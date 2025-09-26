/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "texturesNames.hpp"


// Check, if can load images and preload it
#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)


// File names of the corresponding textures
const char* texturesFilesNames[unsigned(Textures::Count)] = {
    // Graphic interface sprites
    "img/GUI/slider_button.png",
    "img/GUI/slider_line.png",

    "img/GUI/quit_button.png",
    "img/GUI/menu_button.png",
    "img/GUI/save_button.png",
    "img/GUI/settings_button.png",

    // Flags
    "img/GUI/Flag_USA.png",
    "img/GUI/Flag_RUS.png",
    "img/GUI/Flag_GER.png",
    "img/GUI/Flag_BEL.png",

    // Game part
    "img/game/cross.png",
    "img/game/circle.png",
    "img/game/cell.png",

    "img/game/screamer.png",
};

Textures operator+(const Textures _color, int _offset) {
    return Textures(unsigned(_color) + _offset);
}

Textures operator-(const Textures _color, int _offset) {
    return Textures(unsigned(_color) - _offset);
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
