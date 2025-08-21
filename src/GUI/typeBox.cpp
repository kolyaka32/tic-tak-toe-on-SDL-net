/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


template <unsigned bufferSize>
GUI::TypeBox<bufferSize>::TypeBox(const Window& _window, float _posX, float _posY, float _height,
    const char *_startText, Aligment _aligment, unsigned _frameWidth, Color _textColor)
: TypeField<bufferSize>(_window, _posX, _posY, _height, _startText, _aligment, _textColor),
backRect({_posX*_window.getWidth() - (6.5f*bufferSize+2), _posY*_window.getHeight()-_height * 0.9f,
    13.0f * bufferSize+4, _height * 1.8f}) {
    // Creating backplate
    backTexture = Template::window.createTexture(backRect.w, backRect.h);
    Template::window.setRenderTarget(backTexture);
    Template::window.setDrawColor(GREY);
    Template::window.clear();
    Template::window.setDrawColor(WHITE);
    Template::window.drawRect({_frameWidth, _frameWidth, backRect.w-2*_frameWidth, backRect.h-2*_frameWidth});
    Template::window.resetRenderTarget();
}

template <unsigned bufferSize>
GUI::TypeBox<bufferSize>::~TypeBox() {
    SDL_DestroyTexture(backTexture);
}

template <unsigned bufferSize>
void GUI::TypeBox<bufferSize>::blit() const {
    // Rendering background picture for better typing
    Template::window.blit(backTexture, backRect);

    // Rendering text
    TypeField<bufferSize>::blit();
}
