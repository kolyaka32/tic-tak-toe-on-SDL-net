#pragma once

#include "pause.hpp"

// Game cycle, where you create server for play using internet
void multiMainServer();

// Function of showing disconect message
inline void showDisconect(){
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Disconect", "Your connection lost, server disconect", app.window);
        break;
    
    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Соединение потеряно", "Соединение потерено, сервер отключён", app.window);
        break;
    }
};

// Types of internet messages
enum MESSAGE_types{
    MES_INIT = 0,   // Type of starting server and checking compatibility
    MES_START = 1,  // Type of starting new round showing which player start
    MES_NONE = 2,   // Type of nothing for reset connection timer
    MES_TURN = 3,   // Type of setting shape on field, sending to opponent
    MES_STOP = 4,   // Type of closing game and go to menu
    MES_REST = 5    // Type of restarting game and waiting for new MES_START
};