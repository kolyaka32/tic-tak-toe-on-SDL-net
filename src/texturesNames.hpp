/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"


// Check, if can load images and preload it
#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)


// Names of all images with related numbers
enum class Textures : unsigned {
    // Base part
    // Graphic interface sprites
    SliderButton,
    SliderLine,
    QuitButton,
    MenuButton,
    SaveButton,
    SettingsButton,

    // Base flags in settings
    FlagUSA,
    FlagRUS,
    FlagGER,
    FlagBEL,

    // Main game part
    // Game figures
    Cross,
    Circle,
    // Empty cell
    Cell,

    // Additional part
    Screamer,

    // Global counter of all textures
    Count,
};

// Operators for change textures depend on offset
Textures operator+(const Textures index, int offset);
Textures operator-(const Textures index, int offset);

// File names of the corresponding textures
extern const char* texturesFilesNames[unsigned(Textures::Count)];

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
