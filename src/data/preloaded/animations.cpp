/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "animations.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)

#include "loader/loader.hpp"
#include "../exceptions.hpp"


AnimationsData::AnimationsData() {
    // Resetting texture array
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Animations::Count); ++i) {
        animations[i] = nullptr;
    }
    #endif

    // Loading all needed textures
    for (unsigned i=0; i < unsigned(Animations::Count); ++i) {
        loadAnimation(Animations(i), animationsFilesNames[i]);
    }

    // Checking massive on loading correction
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Animations::Count); ++i) {
        if (animations[i] == nullptr) {
            throw DataLoadException(animationsFilesNames[i]);
        }
    }
    logAdditional("Animations loaded corretly");
    #endif
}

AnimationsData::~AnimationsData() {
    // Closing all animations
    for (unsigned i=0; i < unsigned(Animations::Count); ++i) {
        IMG_FreeAnimation(animations[i]);
    }
}

void AnimationsData::loadAnimation(Animations _index, const char* _fileName) {
    // Load data of current texture
    SDL_IOStream* data = dataLoader.load(_fileName);

    // Creating texture
    animations[unsigned(_index)] = IMG_LoadAnimation_IO(data, true);

    // Checking correction of loaded texture
    #if (CHECK_CORRECTION)
    if (animations[unsigned(_index)] == nullptr) {
        throw DataLoadException(_fileName);
    }
    #endif
}

IMG_Animation* AnimationsData::operator[] (Animations _index) const {
    return animations[unsigned(_index)];
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
