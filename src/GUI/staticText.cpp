/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


// Class of static text
GUI::StaticText::StaticText(const Window& _window, float _X, float _Y,
const LanguagedText&& _texts, float _height, Color _color, Aligment _aligment)
: TextureTemplate(_window, _window.createTexture(Fonts::Main, _height, _texts.getString().c_str(), 0, _color)) {
    // Updating rect height for correct button
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = SDL_roundf(_window.getWidth() * _X - (rect.w * (unsigned)_aligment / 2));
    rect.y = SDL_roundf(_window.getHeight() * _Y - rect.h / 2);
}

GUI::StaticText::StaticText(StaticText&& _object) noexcept
: TextureTemplate(std::move(_object)) {}

GUI::StaticText::~StaticText() noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
