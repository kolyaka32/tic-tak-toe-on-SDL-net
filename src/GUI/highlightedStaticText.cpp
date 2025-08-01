/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::HighlightedStaticText::HighlightedStaticText(const Window& _target, float _X, float _Y,
    const LanguagedText _texts, int frame, float _height, Color _color, Aligment _aligment) {
    // Creating texture of text
    TTF_Font* font = _target.getFont(FNT_MAIN);
    TTF_SetFontSize(font, _height);
    TTF_SetFontOutline(font, frame);

    // Creating surface
    SDL_Surface* surface = TTF_RenderText_Solid(font, _texts.getString().c_str(), 0, {1, 0, 0, 255});

    // Resetting outline
    TTF_SetFontOutline(font, 0);
    SDL_Surface* frontSurface = TTF_RenderText_Solid(font, _texts.getString().c_str(), 0, _color);

    // Merging surfaces
    SDL_SetSurfaceBlendMode(frontSurface, SDL_BLENDMODE_NONE);
    _target.setBlendMode(frontSurface);
    SDL_BlitSurface(frontSurface, nullptr, surface, nullptr);
    SDL_DestroySurface(frontSurface);

    // Creating texture from created surface
    texture = _target.createTextureAndFree(surface);

    // Updating rect height for correct button
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SDL_roundf(_target.getWidth() * _X - (rect.w * (unsigned)_aligment / 2));
    rect.y = SDL_roundf(_target.getHeight() * _Y - rect.h / 2);
}

GUI::HighlightedStaticText::~HighlightedStaticText() {
    SDL_DestroyTexture(texture);
}
