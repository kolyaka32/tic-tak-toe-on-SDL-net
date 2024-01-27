#include "include.hpp"
#include "SDL_net.h"

#include "define.hpp"
#include "pause.hpp"
#include "game.hpp"


static bool runGame;   // Flag of running internal game cycle
static bool start;     // Flag of showing welcome screen of choosing command
static bool twoPlayers;  // Flag of mode with two players to show text of 1/2 player instead of you
bool restart = false;  // Flag of restarting game with other parametrs

bool loosing;      // Flag of showing loosing screen
bool winning;      // Flag of showing winning screen
bool nobody;       // Flag of showing screen with nobody win

coord fieldWidth;  // Width and height of field
Uint8 queue;       // Modifictor to change picture of current player (0 for cross, 1 for circle)
Uint8 player;      // Number of player, which selected

static Field field;  // Main game field

// Menu for waiting to restart or go to menu
inline void stopMenu(){
    // Creating buttons
    GUI::Button stopButtons[] = {
        {0.5, 0.7, IMG_MENU_BUTTON, &texts[TXT_STOP_RESTART]},
        {0.5, 0.9, IMG_MENU_BUTTON, &texts[TXT_STOP_MENU]}
    };
    for(Uint8 i=0; i < 2; ++i){
        stopButtons[i].init();
    }

    // Starting Internal loop of waiting for restart/go to menu
    bool waiting = true;
    start = true;
    SDL_Event event;
    while(waiting){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                waiting = false;
                return;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                if(stopButtons[0].in(MouseX, MouseY)){
                    // Restarting round
                    field.reset();
                    start = true;
                    waiting = false;
                }
                else if(stopButtons[1].in(MouseX, MouseY)){
                    // Going to menu
                    runGame = false;
                    waiting = false;
                }
                break;
            }
        }
        // Drawing
        SDL_RenderClear(app.renderer);

        if(winning)
            if(twoPlayers)
                texts[TXT_STOP_WIN_1].blit();
            else
                texts[TXT_STOP_WIN].blit();
        else if(loosing)
            if(twoPlayers)
                texts[TXT_STOP_WIN_2].blit();
            else
                texts[TXT_STOP_LOOSE].blit();
        else if(nobody)
            texts[TXT_STOP_NOBODY].blit();
        
        // Showing buttons
        for(Uint8 i=0; i < 2; ++i){
            stopButtons[i].blit();
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer);

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    // Clearing data
    winning = false;
    loosing = false;
    nobody = false;
    player = 0;
}

// Singleplayer mode of game
void singleMainCycle(){

    // Creating start buttons
    GUI::Button queueButton[] = {
        {0.25, 0.5, IMG_GREEN_CROSS},
        {0.75, 0.5, IMG_GREEN_CIRCLE}
    };

    for(Uint8 i=0; i < 2; ++i){
        queueButton[i].init();
    }

    // Resetting field
    field.reset();
    player = 0;

    // Variables for loop
    SDL_Event event;
    runGame = true;
    start = true;

    // Starting main game loop
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                if(start){
                    if(queueButton[0].in(MouseX, MouseY)){
                        // Activation cross - moving first
                        queue = 0;
                        start = false;
                    }
                    else if(queueButton[1].in(MouseX, MouseY)){
                        // Activating circle - moving second
                        queue = 1;
                        // First move of AI
                        field.AImove();
                        start = false;
                    }
                }
                else {
                    field.clickSingle(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR));
                }
                break;
            }
        }

        // Checking end of game
        if(winning || loosing || nobody){
            stopMenu();
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Showing game chose
        if(start){
            // Showing text for Activation
            texts[TXT_START_SELECT].blit();
            // Showing buttons for chose
            for(Uint8 i=0; i < 2; ++i){
                queueButton[i].blit();
            }
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
}

//
void twoMainCycle(){
    // Resetting field
    field.reset();
    //single = false;
    queue = 0;

    // Variables for loop
    SDL_Event event;
    runGame = true;
    twoPlayers = true;

    // Starting loop for waiting for start
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                field.clickTwo(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR));
                break;
            }
        }

        // Checking end of game
        if(winning || loosing || nobody){
            stopMenu();
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    twoPlayers = false;
}

bool waitTurn;  // Flag of waiting, until another user have his turn

//
void multiMainServer(){
    // Creating ip and port at server, where connect to
    IPaddress ip;
    Uint16 port = BASE_PORT;

    // Finding free port to connect
    while(SDLNet_ResolveHost(&ip, NULL, port)){
        port = rand() % 4000;
    }
    
    TCPsocket server = SDLNet_TCP_Open(&ip);  // Openning TCP port to connect to client
    TCPsocket client = nullptr;

    // Updating text with port to show it
    texts[TXT_SREVER_PORT].updateText(language, port);

    // Creating button to exit waiting
    GUI::Button menuButton = {0.5, 0.9, IMG_MENU_BUTTON, &texts[TXT_STOP_MENU]};
    menuButton.init();

    // Variables for waiting cycle
    SDL_Event event;
    runGame = true;
    start = true;

    // Waiting, when client connect this server
    while(!client && runGame)
    {
        // Trying accept to client
        client = SDLNet_TCP_Accept(server);

        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                SDLNet_TCP_Close(server);
                if(client){
                    SDLNet_TCP_Close(client);
                }
                return;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if(menuButton.in(MouseX, MouseY)){
                    runGame = false;  // Go to menu button
                    SDLNet_TCP_Close(server);
                    if(client){
                        SDLNet_TCP_Close(client);
                    }
                    return;
                }
                break;
            }
        }

        // Drawing
        SDL_RenderClear(app.renderer);

        // Showing text to wait to connect
        texts[TXT_SERVER_WAIT].blit();
        texts[TXT_SREVER_PORT].blit();

        menuButton.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);
    }

    // Checking correction of client version
    Uint8 sendData[5] = {0, 1, fieldWidth, fieldWidth, 0};  // Array to send data to client
    Uint8 recieveData[5];    // Array to save data from client
    SDLNet_TCP_Send(client, sendData, 5);

    // Creating socket set to control trafic
    SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(set, client);

    // Creating start buttons
    GUI::Button queueButton[] = {
        {0.25, 0.5, IMG_GREEN_CROSS},
        {0.75, 0.5, IMG_GREEN_CIRCLE}
    };

    for(Uint8 i=0; i < 2; ++i){
        queueButton[i].init();
    }

    // Clearing field
    field.reset();

    // Activating main cycle
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                if(start){
                    if(queueButton[0].in(MouseX, MouseY)){
                        // Activation cross - moving first
                        player = queue = 0;
                        waitTurn = false;
                        start = false;
                    }
                    else if(queueButton[1].in(MouseX, MouseY)){
                        // Activating circle - moving second
                        player = queue = 1;
                        waitTurn = true;
                        start = false;
                    }
                    // Sending message to client of start
                    sendData[0] = 1;      // Flag of starting game
                    sendData[1] = queue;  // Second position - which move first
                    
                    SDLNet_TCP_Send(client, sendData, 5);
                }
                else if(!waitTurn){
                    field.clickMulti(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR), client);
                    waitTurn = true;
                }
                break;
            }
        }
        // Checking get data
        if(SDLNet_CheckSockets(set, 0)){
            SDLNet_TCP_Recv(client, recieveData, 5);
            switch (recieveData[0])
            {
            case 3:
                // Code of placing at client
                field.clickTwo(recieveData[1], recieveData[2]);
                if(!running){
                    runGame = false;
                    running = true;
                }

                // Allow to current user to make turn
                waitTurn = false;
                break;
            
            case 4:
                // Code of closing game - going to menu
                runGame = false;
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Disconect", "Your connection lost, server disconect", app.window);
                break;
            }
        }

        // Checking end of game
        if(winning || loosing || nobody){
            stopMenu();
            // Sending data of restart to client (if nececery)
            if(runGame){
                sendData[0] = 5;  // Flag of restarting game
                sendData[1] = 0;  // Second position
                
                SDLNet_TCP_Send(client, sendData, 5);
            }
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Showing game chose
        if(start){
            // Showing text for Activation
            texts[TXT_START_SELECT].blit();
            // Showing buttons for chose
            for(Uint8 i=0; i < 2; ++i){
                queueButton[i].blit();
            }
        }
        else{
            if(waitTurn){
                texts[TXT_INTERNET_WAIT].blit();
            }
            else{
                texts[TXT_INTERNET_TURN].blit();
            }
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    // Sending message of server disabling
    sendData[0] = 4;
    sendData[1] = 0;
    SDLNet_TCP_Send(client, sendData, 5);

    // Clearing socket set
    SDLNet_FreeSocketSet(set);

    // Closing port
    SDLNet_TCP_Close(server);
    SDLNet_TCP_Close(client);
}

//
void multiMainClient(){
    // Getting data from user, where connect to
    IPaddress ip;
    // Creating socket
    TCPsocket client = NULL;

    GUI::typeBox IPbox(20, 0.5, 0.25, baseIP.std::string::c_str());
    GUI::typeBox Portbox(20, 0.5, 0.55, basePort.std::string::c_str());

    GUI::Button connectButton(0.5, 0.7, IMG_MENU_BUTTON, texts + TXT_CLIENT_CONNECT);
    GUI::Button menuButton(0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU);
    
    connectButton.init();
    menuButton.init();

    // Main waiting cycle for getting ip and port
    SDL_Event event;
    bool waiting = true;
    runGame = true;
    Uint8 inBox = 0;  // Selected window to interact with (or 0 for none)

    while(waiting){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                waiting = false;
                return;

            case SDL_KEYDOWN:
                // Typing on which object is selected
                switch (inBox)
                {
                case 1:
                    IPbox.press(event.key.keysym.sym);
                    break;
                
                case 2:
                    Portbox.press(event.key.keysym.sym);
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                // Checking pressing on connect button
                if(connectButton.in(MouseX, MouseY)){
                    // Trying connecting at writed coordinats
                    if(SDLNet_ResolveHost(&ip, IPbox.buffer, std::stoi(Portbox.buffer)) != -1){
                        client = SDLNet_TCP_Open(&ip);
                        if(client != NULL){
                            // If connection correct - Starting
                            waiting = false;
                        }
                        else{
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Can't connect", "Can't connect to this addres", app.window);
                        }
                    }
                }
                else if(menuButton.in(MouseX, MouseY)){
                    // Going to menu
                    if(client){
                        SDLNet_TCP_Close(client);
                    }
                    return;
                }
                else{
                    if(IPbox.in(MouseX, MouseY)){
                        inBox = 1;
                    }
                    else if(Portbox.in(MouseX, MouseY)){
                        inBox = 2;
                    }
                    else{
                        inBox = 0;
                    }
                    break;
                }
            }
        }

        // Drawing
        SDL_RenderClear(app.renderer);

        texts[TXT_CLIENT_IP].blit();
        IPbox.blit();
        texts[TXT_CLIENT_PORT].blit();
        Portbox.blit();

        connectButton.blit();
        menuButton.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);
    }

    // Creating socket set to control trafic
    SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(set, client);

    Uint8 recieveData[5];  // Array to save data from server
    Uint8 sendData[5];     // Arrat to send data to server
 
    // Getting test data from server to control correction
    while(SDLNet_TCP_Recv(client, recieveData, 5) == 0);
    if(recieveData[0] || recieveData[1] != 1 || recieveData[2] != fieldWidth || recieveData[3] != fieldWidth || recieveData[4]){
        // Something wrong with test pachage
        running = false;
        runGame = false;
        
        // Asking for restart game with other settings
        // Creating button for asking to restart
        const SDL_MessageBoxColorScheme colorScheme = {{
                { 255,   0,   0 },
                {   0, 255,   0 },
                { 255, 255,   0 },
                {   0,   0, 255 },
                { 255,   0, 255 }
            }};
        const SDL_MessageBoxData* messageBox;
        
        if(language == LNG_ENGLISH){
            const SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "cancel" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "reload" },
            };
            const SDL_MessageBoxData messageboxdata = {
                SDL_MESSAGEBOX_WARNING,
                app.window,
                "Data doesn't match",
                "Your load configuration donesn't match with server, do you want restart?",
                SDL_arraysize(buttons),
                buttons,
                &colorScheme
            };
            messageBox = &messageboxdata;
        }
        else{
            const SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "отмена" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "перезагрузка" },
            };
            const SDL_MessageBoxData messageboxdata = {
                SDL_MESSAGEBOX_WARNING,
                app.window,
                "Данные не сходятся",
                "Ваши загруженные данные не сходятся с сервером, хотите перезагрузится?",
                SDL_arraysize(buttons),
                buttons,
                &colorScheme
            };
            messageBox = &messageboxdata;
        }

        int buttonid;  // Getting answer from massage
        SDL_ShowMessageBox(messageBox, &buttonid);
        if (buttonid == 2) {
            // If user want to reload
            restart = true;
            fieldWidth = recieveData[2];
        }
        running = false;
        runGame = false;
    }
    else{
        // Saving exntered parametrs for next conncetion
        basePort = IPbox.buffer;
        basePort = Portbox.buffer;
    }

    // Preparing for game
    field.reset();
    waitTurn = true;
    start = true;

    // Activating main cycle
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                if(!(start || waitTurn)){
                    field.clickMulti(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR), client);
                    waitTurn = true;
                }
                break;
            }
        }
        // Checking closing connection
        // Checking get data
        if(SDLNet_CheckSockets(set, 0)){
            SDLNet_TCP_Recv(client, recieveData, 5);
            switch (recieveData[0])
            {
            case 1:
                // Getting start
                start = false;

                queue = 1 - recieveData[1];  // Inverting order of players
                player = 1 - recieveData[1];
                waitTurn = 1 - recieveData[1];
                break;

            case 3: 
                // Code of placing at client
                field.clickTwo(recieveData[1], recieveData[2]);

                // Allow to current user to make turn
                waitTurn = false;
                break;
            
            case 4:
                // Code of closing game - going to menu
                runGame = false;
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Disconect", "Your connection lost, server disconect", app.window);
                break;
            }
        }

        // Checking end of game
        if(winning || loosing || nobody){
            // His own waiting menu

            // Creating buttons
            GUI::Button menuButton = {0.5, 0.9, IMG_MENU_BUTTON, &texts[TXT_STOP_MENU]};
            menuButton.init();

            // Starting Internal loop of waiting for restart/go to menu
            bool waiting = true;
            
            SDL_Event event;
            while(waiting){
                while( SDL_PollEvent(&event) != 0 ){
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        running = false;  // Exit from program
                        runGame = false;
                        waiting = false;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        int MouseX, MouseY;
                        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                        if(menuButton.in(MouseX, MouseY)){
                            // Going to menu
                            runGame = false;
                            waiting = false;
                        }
                        break;
                    }
                }
                // Getting network conncetion
                if(SDLNet_CheckSockets(set, 0)){
                    SDLNet_TCP_Recv(client, recieveData, 5);
                    switch (recieveData[0])
                    {
                    case 4:
                        // Exit program code
                        // Going to menu
                        runGame = false;
                        waiting = false;
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Disconect", "Your connection lost, server disconect", app.window);
                        break;
                    
                    case 5:
                        // Restart game code
                        waiting = false;
                        field.reset();
                        break;
                    }
                }

                // Drawing
                SDL_RenderClear(app.renderer);

                if(winning)
                    texts[TXT_STOP_WIN].blit();
                else if(loosing)
                    texts[TXT_STOP_LOOSE].blit();
                else if(nobody)
                    texts[TXT_STOP_NOBODY].blit();
                
                // Showing buttons
                menuButton.blit();

                // Blitting textures on screen
                SDL_RenderPresent(app.renderer);

                // Delaying time to decrease CPU loading
                SDL_Delay(1000 / drawFPS);  
            }
            // Clearing data
            winning = false;
            loosing = false;
            nobody = false;
            player = 0;
            start = true;
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Showing game chose
        if(start){
            // Showing text for Activation
            texts[TXT_CLIENT_START].blit();
        }
        else{
            if(waitTurn){
                texts[TXT_INTERNET_WAIT].blit();
            }
            else{
                texts[TXT_INTERNET_TURN].blit();
            }
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }

    // Sending message of client disable
    sendData[0] = 4;
    sendData[1] = 0;
    SDLNet_TCP_Send(client, sendData, 5);

    // Clearing socket set
    SDLNet_FreeSocketSet(set);
    
    // Clearing network socekt
    SDLNet_TCP_Close(client);
}