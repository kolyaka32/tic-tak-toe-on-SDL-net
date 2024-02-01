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
static TCPsocket client;                    // Socket for connection
static SDLNet_SocketSet set;                // Network set for checking for new messages
static IPaddress ip;                        // Summary ip addres, connect to
static Uint8 recieveData[INTERNET_BUFFER];  // Array to save data from server
static Uint8 sendData[INTERNET_BUFFER];     // Array to send data to server
static Uint64 lastMessageArrive;            // Timer, when last message arrive to control connection
static Uint64 lastMessageSend;              // Timer, when last message send to control connection


// Macros for removing select from typeBox
#define removeTypeBox() if(inBox){\
    typeBoxes[inBox - 1].removeSelect();\
    inBox = 0; }

// Function of trying connect to writed coordinats
static inline void tryConnect(const char* ipText, const char* portText, bool* waiting){
    if(SDLNet_ResolveHost(&ip, ipText, std::stoi(portText)) != -1){
        client = SDLNet_TCP_Open(&ip);
        if(client != NULL){
            // If connection correct - Starting
            *waiting = false;
            // Saving entered parameters for next conncetion
            baseIP = (std::string)ipText;
            basePort = (std::string)portText;
            return;
        }
        else{
            switch (language)
            {
            case LNG_ENGLISH:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Can't connect", "Can't connect to given address", app.window);
                break;
            
            case LNG_RUSSIAN:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Невозможно присоединится", "Невозможно присоединится по указанному адресу", app.window);
                break;
            }
            return;
        }
    }
}

// Cycle for user enter, where connect to
static inline Uint8 enteringCycle(){
    // Creating internal GUI
    // Boxes for typing text in
    GUI::typeBox typeBoxes[] = {
        {20, 0.5, 0.25, baseIP.std::string::c_str()},
        {20, 0.5, 0.55, basePort.std::string::c_str()}
    };
    // Buttons to connect/got to menu
    GUI::Button connectButton(0.5, 0.7, IMG_MENU_BUTTON, texts + TXT_CLIENT_CONNECT);
    GUI::Button menuButton(0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU);
    // Button initialasing
    connectButton.init();
    menuButton.init();

    // Waiting cycle for getting ip and port
    SDL_Event event;
    
    bool waiting = true;       // Flag of internal cycle
    Uint8 inBox = 0;           // Selected window to interact with (or 0 for none)
    Uint64 lastTypeBoxUpdate;  // Timer for change symbol of caret

    while(waiting){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return 1;

            case SDL_TEXTINPUT:
                // Typing text on which object is selected
                if(inBox){
                    typeBoxes[inBox - 1].writeString(event.text.text, false);
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    removeTypeBox();
                    break;
                
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                    removeTypeBox();
                    tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer, &waiting);
                    break;
                
                default:
                    if(inBox){
                        typeBoxes[inBox - 1].press(event.key.keysym.sym);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                // Checking pressing on connect button
                if(connectButton.in(MouseX, MouseY)){
                    removeTypeBox();
                    tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer, &waiting);
                }
                else if(menuButton.in(MouseX, MouseY)){
                    // Returning to menu
                    removeTypeBox();
                    runGame = false;
                    return 2;
                }
                else if(typeBoxes[0].in(MouseX, MouseY)){
                    if(inBox != 1){
                        inBox = 1;
                        typeBoxes[0].select();
                        lastTypeBoxUpdate = SDL_GetTicks64() + 700;
                    }
                }
                else if(typeBoxes[1].in(MouseX, MouseY)){
                    if(inBox != 2){
                        inBox = 2;
                        typeBoxes[1].select();
                        lastTypeBoxUpdate = SDL_GetTicks64() + 700;
                    }
                }
                else{
                    removeTypeBox();
                }
                break;
            }
        }

        // Checking, if need to blink in type box
        if(inBox && (SDL_GetTicks64() > lastTypeBoxUpdate)){
            // Updating type box for show place to type
            typeBoxes[inBox-1].updateCaret();
            lastTypeBoxUpdate = SDL_GetTicks64() + 500;
        }

        // Drawing
        SDL_RenderClear(app.renderer);

        texts[TXT_CLIENT_IP].blit();
        typeBoxes[0].blit();
        texts[TXT_CLIENT_PORT].blit();
        typeBoxes[1].blit();

        connectButton.blit();
        menuButton.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);
    }
    return 0;  // Exiting without any errors
}

// Menu for waiting to go to menu/game restart (from server)
static inline void stopMenu(){
    // Creating buttons
    GUI::Button menuButton = {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU};
    menuButton.init();

    // Starting internal loop of waiting for restart/go to menu
    bool waiting = true;
    
    SDL_Event event;
    while(waiting){
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

                if(menuButton.in(MouseX, MouseY)){
                    // Going to menu
                    runGame = false;
                    return;
                }
                break;
            }
        }
        // Checking, if need to send NULL-message
        if(SDL_GetTicks64() > lastMessageSend){
            sendData[0] = MES_NONE;
            SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
            lastMessageSend = SDL_GetTicks64();
        }
        // Getting network conncetion
        if(SDLNet_CheckSockets(set, 0)){
            SDLNet_TCP_Recv(client, recieveData, INTERNET_BUFFER);
            switch (recieveData[0])
            {
            case MES_STOP:
                // Going to menu
                runGame = false;
                waiting = false;
                showDisconect();
                break;
            
            case MES_REST:
                // Restart game code
                waiting = false;
                field.reset();
                player = 0;
                start = true;
                break;
            };
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_TIMEOUT;
        }
        else{
            if(SDL_GetTicks64() > lastMessageArrive){
                // Something wrong with connection
                showDisconect();
                runGame = false;
                return;
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
    // Resetting data
    winning = false;
    loosing = false;
    nobody = false;
}

// Main game cycle
static inline void gameCycle(){
    // Preparing for game
    SDL_Event event;
    field.reset();
    waitTurn = true;
    start = true;
    // Resetting messgae timeout
    lastMessageArrive = SDL_GetTicks64() + MESSAGE_TIMEOUT * 2;
    lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL * 2;

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
                    if(field.clickMulti(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR), client, &lastMessageSend)){
                        waitTurn = true;
                    }
                }
                break;
            }
        }
        // Checking, if need to send NULL-message
        if(SDL_GetTicks64() > lastMessageSend){
            sendData[0] = MES_NONE;
            SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
            lastMessageSend = SDL_GetTicks64();
        }
        // Checking closing connection
        // Checking get data
        if(SDLNet_CheckSockets(set, 0)){
            SDLNet_TCP_Recv(client, recieveData, INTERNET_BUFFER);
            switch (recieveData[0])
            {
            case MES_START:
                // Getting start
                start = false;

                queue = 1 - recieveData[1];  // Inverting order of players
                player = queue;
                waitTurn = queue;
                break;

            case MES_TURN: 
                // Code of opponent placing shape
                if(!start){
                    field.clickTwo(recieveData[1], recieveData[2]);
                    // Allow to current user to make turn
                    waitTurn = false;
                }
                break;
            
            case MES_STOP:
                // Code of closing game - going to menu
                runGame = false;
                showDisconect();
                break;

            case MES_REST:
                // Code of restart game
                field.reset();
                player = 0;
                start = true;
                waitTurn = true;
                break;
            }
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_TIMEOUT;
        }
        else{
            if(SDL_GetTicks64() > lastMessageArrive){
                // Something wrong with connection
                showDisconect();
                runGame = false;
                return;
            }
        }

        // Checking end of game
        if(winning || loosing || nobody){
            // His own waiting menu
            stopMenu();
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
    sendData[0] = MES_STOP;
    SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
}

// Main game client cycle
void multiMainClient(){
    // Setting main game cycle to run after "entering cycle"
    runGame = true;

    // Getting data from user, where connect to
    if(enteringCycle()){
        // Exiting program to menu
        return;
    }
 
    // Getting test data from server to control correction
    while(SDLNet_TCP_Recv(client, recieveData, INTERNET_BUFFER) == 0);  // Waiting to get first init data
    if(recieveData[0] || recieveData[1] != fieldWidth || recieveData[2] != winWidth){
        // Something wrong with test pachage
        
        // Creating button for asking to restart
        const SDL_MessageBoxColorScheme colorScheme = {{
            { 255,   0,   0 },
            {   0, 255,   0 },
            { 255, 255,   0 },
            {   0,   0, 255 },
            { 255,   0, 255 }
        }};
        int buttonid = 0;  // Field for answer
        
        if(language == LNG_ENGLISH){
            const SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "cancel" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "reload" },
            };
            const SDL_MessageBoxData messageBox = {
                SDL_MESSAGEBOX_WARNING,
                app.window,
                "Data doesn't match",
                "Your load configuration donesn't match with server, do you want restart?",
                SDL_arraysize(buttons),
                buttons,
                &colorScheme
            };
            SDL_ShowMessageBox(&messageBox, &buttonid);
        }
        else{
            const SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "отмена" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "перезагрузка" },
            };
            const SDL_MessageBoxData messageBox = {
                SDL_MESSAGEBOX_WARNING,
                app.window,
                "Данные не сходятся",
                "Ваши загруженные данные не сходятся с сервером, хотите перезагрузится?",
                SDL_arraysize(buttons),
                buttons,
                &colorScheme
            };
            SDL_ShowMessageBox(&messageBox, &buttonid);
        }
        // Checking answer
        if (buttonid == 2) {
            // If user want to reload
            restart = true;
            fieldWidth = recieveData[1];
            winWidth = recieveData[2];
            running = false;
        }
        // Sending code of stopping
        sendData[0] = MES_STOP;
        SDLNet_TCP_Send(client, sendData, INTERNET_BUFFER);
        
        // Clearing network socket
        SDLNet_TCP_Close(client);
        return;
    }

    // Creating socket set to control new messages
    set = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(set, client);

    // Entering main game cycle, where he play
    gameCycle();

    // Clearing socket set
    SDLNet_FreeSocketSet(set);
    
    // Clearing network socekt
    SDLNet_TCP_Close(client);
}