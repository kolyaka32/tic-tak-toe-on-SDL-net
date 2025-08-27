/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../texturesNames.hpp"

// Check, if can load images and preload it
#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
#include <SDL3/SDL_render.h>


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

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
