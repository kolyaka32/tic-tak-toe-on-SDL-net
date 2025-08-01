/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/textures.cpp"


// Names of all images with related numbers
enum IMG_names : unsigned {
    // Base part
    // Graphic interface sprites
    IMG_GUI_PAUSE_BUTTON,
    IMG_GUI_SLIDER_BUTTON,
    IMG_GUI_SLIDER_LINE,
    IMG_GUI_TYPE_BOX,
    IMG_GUI_QUIT_BUTTON,
    IMG_GUI_RESTART_BUTTON,

    // Base flags in settings
    IMG_GUI_FLAG_USA,
    IMG_GUI_FLAG_RUS,
    IMG_GUI_FLAG_GER,
    IMG_GUI_FLAG_BEL,

    // Main game part
    // Green (current player) figures
    IMG_GREEN_CROSS,
    IMG_RED_CROSS,

    // Red (opponent player) figures
    IMG_GREEN_CIRCLE,
    IMG_RED_CIRCLE,

    // Empty cell
    IMG_CELL,

    // Additional part
    IMG_SCREAMER,

    // Global counter of all textures
    IMG_count,
};

// File names of the corresponding textures
extern const char* texturesFilesNames[IMG_count];
