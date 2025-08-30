/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../fontsNames.hpp"

// Check, if use fonts and preload it
#if (USE_SDL_FONT) && (PRELOAD_FONTS)

#include <SDL3_ttf/SDL_ttf.h>


// Class for get font with need height
class FontsData {
 private:
    TTF_Font* fonts[unsigned(Fonts::Count)];
    void loadFont(Fonts index, const char* fileName);

 public:
    FontsData();
    ~FontsData();
    TTF_Font* operator[](Fonts index) const;
};

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
