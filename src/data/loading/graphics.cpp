/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "graphics.hpp"

// Class of textures array
Textures::Textures(const char **_filesNames, SDL_Renderer *_renderer) {
    // Resetting list of textures
    #if CHECK_CORRECTION
    memset(textures, 0, IMG_count * sizeof(textures[0]));
    #endif

    // Loading all images
    // loadTexture(".png", IMG_);  // Template
    for (Uint8 i = 0; i < IMG_count; ++i) {
        loadTexture(_filesNames[i], i, _renderer);
    }
    

    // Checking correction of all loaded images
    #if CHECK_CORRECTION
    checkCorrection();
    #endif
}

Textures::~Textures() {
    // Clearing all textures after work
    for (Uint8 i = 0; i < IMG_count; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

void Textures::loadTexture(const std::string _name, unsigned _index, SDL_Renderer *_renderer) {
    // Getting selected picture data
    SDL_RWops *tempRW = loadObject("img/" + _name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if (!tempRW) {
        throw DataLoadException("image file load: " + _name);
    }
    #endif

    // Creating surface from data
    SDL_Surface *tempSurface = IMG_Load_RW(tempRW, 0);

    // Freeing picture data
    #if ARCHIEVE_LOADING
    free(tempRW->hidden.mem.base);
    #endif
    SDL_RWclose(tempRW);

    // Creating texture from surface and setting to it place
    textures[_index] = SDL_CreateTextureFromSurface(_renderer, tempSurface);

    // Clearing data
    SDL_FreeSurface(tempSurface);

    // Checking correction of loaded texture
    #if CHECK_CORRECTION
    if (textures[_index] == nullptr) {
        throw DataLoadException("image file creation: " + _name);
    }
    #endif
}

// Checking correction of loaded textures
#if CHECK_CORRECTION
void Textures::checkCorrection() const {
    // Checking, if all images exist
    for (Uint8 i = 0; i < IMG_count; ++i) {
        if (textures[i] == NULL) {
            throw DataLoadException("image files wrong count");
        }
    }
}
#endif

SDL_Texture** Textures::getTextures() {
    return textures;
}
