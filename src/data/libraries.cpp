/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "libraries.hpp"
// External libraries for initialisation
#if (CHECK_CORRECTION)
#include "exceptions.hpp"
#endif
#include <SDL3/SDL.h>
#if (USE_SDL_FONT)
#include <SDL3_ttf/SDL_ttf.h>
#endif
#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#endif
#include "../internet/library.hpp"


Libraries::Libraries() {
    // Load depend on testing
    #if (CHECK_CORRECTION)
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        throw LibararyLoadException("Main library: " + std::string(SDL_GetError()));
    }

    // Initialasing font library
    #if (USE_SDL_FONT)
    if (!TTF_Init()) {
        throw LibararyLoadException("Font library: " + std::string(SDL_GetError()));
    }
    #endif
    logAdditional("Libraries load correctly");

    #else  // (CHECK_CORRECTION)
    // Loading without checking correction

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    #if (USE_SDL_FONT)
    TTF_Init();
    #endif

    #endif  // (CHECK_CORRECTION)
}

Libraries::~Libraries() noexcept {
    // Closing trueTypeFont library
    #if (USE_SDL_FONT)
    TTF_Quit();
    #endif

    // Closing main SDL library
    SDL_Quit();
}
