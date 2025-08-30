/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../animationsNames.hpp"

// Check, if can load animations and should preload it
#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
#include <SDL3_image/SDL_image.h>


// Class for load, get and clear preloaded animations
class AnimationsData {
 private:
    IMG_Animation* animations[unsigned(Animations::Count)];
    void loadAnimation(Animations name, const char* fileName);

 public:
    explicit AnimationsData();
    ~AnimationsData();
    IMG_Animation* operator[] (Animations name) const;
};

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
