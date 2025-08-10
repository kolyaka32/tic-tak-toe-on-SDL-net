/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include "loader/loader.hpp"
#include "../../fontsNames.hpp"


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
