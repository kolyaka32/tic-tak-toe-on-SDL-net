/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


template <unsigned bufferSize>
GUI::TypeBox<bufferSize>::TypeBox(const Window& _window, float _posX, float _posY, float _height,
    const char *_startText, Aligment _aligment, unsigned _frameWidth, Color _textColor)
: TypeField<bufferSize>(_window, _posX, _posY, _height, _startText, _aligment, _textColor),
backplate(_window, {_posX*_window.getWidth() - (6.5f*bufferSize+2), _posY*_window.getHeight()-_height * 0.9f,
    13.0f * bufferSize+4, _height * 1.9f}, 2) {}

template <unsigned bufferSize>
void GUI::TypeBox<bufferSize>::blit() const {
    // Rendering background picture for better typing
    backplate.blit();

    // Rendering text
    TypeField<bufferSize>::blit();
}

template <unsigned bufferSize>
bool GUI::TypeBox<bufferSize>::in(const Mouse _mouse) const {
    return backplate.in(_mouse);
}
