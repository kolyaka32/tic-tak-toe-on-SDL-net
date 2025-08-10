/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_image/SDL_image.h>
#include "loader/loader.hpp"


// Class for load, draw and clear textures
template <unsigned count>
class TexturesData {
 private:
    SDL_Texture* textures[count];
    void loadTexture(SDL_Renderer* renderer, unsigned index, const char* name);

 public:
    TexturesData(SDL_Renderer* renderer, const char* names[count]);
    ~TexturesData();
    SDL_Texture* operator[] (unsigned index) const;
};
