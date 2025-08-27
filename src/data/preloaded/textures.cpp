/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "textures.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)

#include <SDL3_image/SDL_image.h>
#include "loader/loader.hpp"
#include "../exceptions.hpp"


TexturesData::TexturesData(SDL_Renderer* _renderer) {
    // Resetting texture masiive
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Textures::Count); ++i) {
        textures[i] = nullptr;
    }
    #endif

    // Loading all needed textures
    for (unsigned i=0; i < unsigned(Textures::Count); ++i) {
        loadTexture(_renderer, Textures(i), texturesFilesNames[i]);
    }

    // Checking massive on loading correction
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Textures::Count); ++i) {
        if (textures[i] == NULL) {
            throw DataLoadException(texturesFilesNames[i]);
        }
    }
    logAdditional("Textures loaded corretly");
    #endif
}

TexturesData::~TexturesData() {
    // Closing all used textures
    for (unsigned i=0; i < unsigned(Textures::Count); ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

void TexturesData::loadTexture(SDL_Renderer* _renderer, Textures _index, const char* _fileName) {
    // Load data of current texture
    SDL_IOStream* iodata = dataLoader.load(_fileName);

    // Creating surface
    SDL_Surface* surface = IMG_Load_IO(iodata, true);

    // Checking correction of created surface
    #if (CHECK_CORRECTION)
    if (surface == nullptr) {
        throw DataLoadException(_fileName);
    }
    #endif

    // Creating texture
    textures[unsigned(_index)] = SDL_CreateTextureFromSurface(_renderer, surface);

    // Checking correction of loaded texture
    #if (CHECK_CORRECTION)
    if (textures[unsigned(_index)] == nullptr) {
        throw DataLoadException(_fileName);
    }
    #endif

    SDL_DestroySurface(surface);
}

SDL_Texture* TexturesData::operator[] (Textures _index) const {
    return textures[unsigned(_index)];
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
