/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"


// Check, if can load animations and should preload it
#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)


// Names of all images with related numbers
enum class Animations : unsigned {

    // Count of all animations
    Count,
};

// File names of the corresponding animations
extern const char* animationsFilesNames[unsigned(Animations::Count)];

#endif  // (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
