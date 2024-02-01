#include "include.hpp"
#include "SDL_net.h"
#include "define.hpp"
#include "structs.hpp"
#include "pause.hpp"
#include "gameServer.hpp"

// Data for multiplayer version
static bool waitTurn;  // Flag of waiting, until another user have his turn
static bool runGame;   // Flag of running main game cycle
static bool start;     // Flag of showing welcome screen with choosing command
static Field field;    // Main game object

// Data for internet connection
static TCPsocket server;                    // Socket for server
static TCPsocket client;                    // Socket for connection to client
static SDLNet_SocketSet set;                // Network set for checking for new messages
static Uint8 recieveData[INTERNET_BUFFER];  // Array to save data from server
static Uint8 sendData[INTERNET_BUFFER];     // Arrat to send data to server


// Waiting menu
static inline Uint8 waitingMenu(){
    // Creating button to exit waiting
    GUI::Button menuButton = {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU};
    menuButton.init();

    // Variables for waiting cycle
    SDL_Event event;

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
                return 1;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if(menuButton.in(MouseX, MouseY)){
                    runGame = false;  // Go to menu button
                    SDLNet_TCP_Close(server);
                    if(client){
                        SDLNet_TCP_Close(client);
                    }
                    return 2;
                }
                break;
            }
        }

        // Drawing
        SDL_RenderClear(app.renderer);

        // Showing text to wait to connect
        texts[TXT_SERVER_WAIT].blit();
        texts[TXT_SERVER_PORT].blit();

        menuButton.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);
    }
    return 0;
}

// Menu for waiting to restart or go to menu
static inline void stopMenu(){
    // Creating buttons
    GUI::Button stopButtons[] = {
        {0.5, 0.7, IMG_MENU_BUTTON, texts + TXT_STOP_RESTART},
        {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU}
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
                    // Sending data of restart to client
                    sendData[0] = 5;  // Flag of restarting game
                    sendData[1] = 0;  // Second position
                
                    SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
                }
                else if(stopButtons[1].in(MouseX, MouseY)){
                    // Going to menu
                    runGame = false;
                    waiting = false;
                }
                break;
            }
        }
        // Checking for closing connection
        // Checking for avalible data
        if(SDLNet_CheckSockets(set, 0)){
            SDLNet_TCP_Recv(client, recieveData, INTERNET_BUFFER);
            switch (recieveData[0])
            {
            case MES_STOP:
                // Code of closing game - going to menu
                runGame = false;
                waiting = false;
                showDisconect();
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

// Main game cycle
static inline void gameCycle(){
    // Creating start buttons
    GUI::Button queueButton[] = {
        {0.25, 0.5, IMG_GREEN_CROSS},
        {0.75, 0.5, IMG_GREEN_CIRCLE}
    };
    // Initialasing buttons
    for(Uint8 i=0; i < 2; ++i){
        queueButton[i].init();
    }

    // Clearing field
    SDL_Event event;
    field.reset();
    start = true;

    // Activating main cycle
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                break;;

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
                    
                    SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
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
            SDLNet_TCP_Recv(client, recieveData, INTERNET_BUFFER);
            switch (recieveData[0])
            {
            case MES_TURN:
                // Code of placing at client
                field.clickTwo(recieveData[1], recieveData[2]);

                // Allow to current user to make turn
                waitTurn = false;
                break;
            
            case MES_STOP:
                // Code of closing game - going to menu
                runGame = false;
                showDisconect();
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
    sendData[0] = MES_STOP;
    SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
}

void multiMainServer(){
    // Creating ip and port at server, where connect to
    IPaddress ip;
    Uint16 port = BASE_PORT;

    // Finding free port to connect
    while(SDLNet_ResolveHost(&ip, NULL, port)){
        port = rand() % 4000;
    }
    
    // Openning TCP port to connect to client
    server = SDLNet_TCP_Open(&ip);  
    client = nullptr;

    // Updating text with port to show it
    texts[TXT_SERVER_PORT].updateText(language, port);

    runGame = true;

    // Starting cycle for waiting to connect
    if(waitingMenu()){
        // Going to main game menu
        return;
    }

    // Checking correction of client version
    sendData[0] = MES_INIT;
    sendData[1] = fieldWidth;
    sendData[2] = winWidth;
    SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);  // Sending initialse data to check correction

    // Creating socket set to control trafic
    set = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(set, client);

    gameCycle();

    // Clearing socket set
    SDLNet_FreeSocketSet(set);

    // Closing port
    SDLNet_TCP_Close(server);
    SDLNet_TCP_Close(client);
}
