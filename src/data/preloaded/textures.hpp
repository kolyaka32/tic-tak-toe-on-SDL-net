/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_image/SDL_image.h>
#include "loader/loader.hpp"
#include "../../texturesNames.hpp"


// Class for load, draw and clear textures
class TexturesData {
 private:
    SDL_Texture* textures[unsigned(Textures::Count)];
    void loadTexture(SDL_Renderer* renderer, Textures name, const char* fileName);

 public:
    explicit TexturesData(SDL_Renderer* renderer);
    ~TexturesData();
    SDL_Texture* operator[] (Textures name) const;
};
