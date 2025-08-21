/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::RectBackplate::RectBackplate(const Window& _window, float _centerX, float _centerY, float _width, float _height,
    float _border, Color _frontColor, Color _backColor)
: RectBackplate(_window, {_window.getWidth() * (_centerX - _width/2), _window.getHeight() * (_centerY - _height/2),
    _window.getWidth() * _width, _window.getHeight() * _height}, _border, _frontColor, _backColor) {}

GUI::RectBackplate::RectBackplate(const Window& _window, const SDL_FRect& _rect, float _border,
    Color _frontColor, Color _backColor)
: TextureTemplate(_window) {
    // Copying parameters
    rect = _rect;
    // Creating backplate
    texture = window.createTexture(rect.w, rect.h);
    window.setRenderTarget(texture);
    window.setDrawColor(GREY);
    window.clear();
    window.setDrawColor(WHITE);
    window.drawRect({_border, _border, rect.w-2*_border, rect.h-2*_border});
    window.resetRenderTarget();
}

GUI::RectBackplate::~RectBackplate() {
    SDL_DestroyTexture(texture);
}
