/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)


GUI::ImageButton::ImageButton(const Window& _window, float _X, float _Y, float _width, Textures _index)
: TextureTemplate(_window) {
    // Setting base texture
    texture = window.getTexture(_index);

    // Setting destination
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.w = _width * window.getWidth();
    rect.h = texture->h * rect.w / texture->w;

    rect.x = window.getWidth() * _X - rect.w / 2;
    rect.y = window.getHeight() * _Y - rect.h / 2;
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
