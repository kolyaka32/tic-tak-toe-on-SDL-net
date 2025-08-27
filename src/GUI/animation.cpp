/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)


GUI::Animation::Animation(SDL_Rect _rect, ANI_names _type)
: dest(_dest), type(_type), frame(0), prevTick(0) {}

GUI::Animation::~Animation() {
    SDL_DestroyTexture(texture);
}

void GUI::Animation::blit() {
    if (SDL_GetTicks() > prevTick) {
        static unsigned frame = (frame + 1) % Animations[type]->count;
        window.destroy(texture);
        texture = window.createTexture(Animations[type]->frames[frame], false);
        prevTick = SDL_GetTicks() + Animations[type]->delays[frame] / 2;
    }
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
