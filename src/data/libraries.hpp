/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"
// Check, if use audio in project
#if (USE_SDL_MIXER)
#include <SDL3/SDL_audio.h>
#endif


// Class for load and close needed libraries
class Libraries {
 private:
    #if (USE_SDL_MIXER)
    SDL_AudioDeviceID audioDeviceID = 0;
    #endif

 public:
    Libraries();
    ~Libraries() noexcept;
};
