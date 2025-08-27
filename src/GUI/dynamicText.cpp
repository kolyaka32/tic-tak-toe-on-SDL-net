/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::DynamicText::DynamicText(const Window& _window, float _X, float _Y,
    const LanguagedText _texts, float _height, Color _color, Aligment _aligment)
: TextureTemplate(_window),
posX(_X),
aligment(_aligment),
color(_color),
texts(_texts),
height(_height) {
    rect.y = window.getHeight() * _Y - height / 2;
    // Creating surface with text
    texture = window.createTexture(Fonts::Main, height, texts.getString().c_str(), 0, color);

    // Moving draw rect to new place
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = window.getWidth() * posX - (rect.w * (unsigned)aligment / 2);
}

GUI::DynamicText::~DynamicText() {
    SDL_DestroyTexture(texture);
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
