/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


// Class of static text
GUI::StaticText::StaticText(const Window& _window, float _X, float _Y,
const LanguagedText _texts, float _height, Color _color, Aligment _aligment)
: TextureTemplate(_window) {
    // Creating texture of text
    texture = window.createTexture(Fonts::Main, _height, _texts.getString().c_str(), 0, _color);

    // Updating rect height for correct button
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SDL_roundf(window.getWidth() * _X - (rect.w * (unsigned)_aligment / 2));
    rect.y = SDL_roundf(window.getHeight() * _Y - rect.h / 2);
}

GUI::StaticText::~StaticText() {
    SDL_DestroyTexture(texture);
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
