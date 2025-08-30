/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"


// Check, if use mixer and preload sounds
#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)


// Names of sound effects
enum class Sounds : unsigned {
    // Game part
    Turn,
    Reset,
    Win,
    Loose,

    // Internet connection part
    Disconnect,

    // Screamer
    Screamer,

    // Global counter of all loaded sounds
    Count,
};

// File names of the corresponding sounds
extern const char* soundsFilesNames[unsigned(Sounds::Count)];

#endif  // (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
