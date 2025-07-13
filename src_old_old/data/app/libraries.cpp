/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"

#include "libraries.hpp"
#include "exceptions.hpp"


// Class of libraries initialisation
Libraries::Libraries() {
    // Initialising main libarary
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("main library");
        #endif
    }
    // Initializing image library
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("image library");
        #endif
    }
    // Initialasing font library
    if (TTF_Init()) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("font library");
        #endif
    }
    // Initializing audio library
    if (!Mix_Init(MIX_INIT_OGG)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("audio library");
        #endif
    }
    // Openning audio chanel
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("audio chanel");
        #endif
    }
    // Initialising internet library
    if (SDLNet_Init()) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("internet library");
        #endif
    }
}

Libraries::~Libraries() {
    // Closing all side libraries
    // Internet library
    SDLNet_Quit();
    // Audio chanel
    Mix_CloseAudio();
    // Audio library
    Mix_Quit();
    // Font library
    TTF_Quit();
    // Image library
    IMG_Quit();
    // Main library
    SDL_Quit();
}
