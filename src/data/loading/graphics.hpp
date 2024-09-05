/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL_image.h>
#include <string>
#include "../textures.hpp"
#include "dataLoader.hpp"


// Class of loaded textures for renderer
class Textures : public virtual DataLoader {
 private:
    // Load texture with need name
    void loadTexture(const std::string name, unsigned index, SDL_Renderer *renderer);

	// Array of pointers to textures
	SDL_Texture *textures[IMG_count];

    #if CHECK_CORRECTION
    // Check, if all textures load correctly
    void checkCorrection() const;
    #endif
 public:
    Textures(const char **_filesNames, SDL_Renderer *renderer);
    ~Textures();
    SDL_Texture** getTextures();
};
