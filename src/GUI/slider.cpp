/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)


GUI::Slider::Slider(const Window& _window, float _X, float _Y, float _width, unsigned _startValue,
    Textures _lineImage, Textures _buttonImage, unsigned _max)
: TextureTemplate(_window),
maxValue(_max) {
    // Getting need texture
    texture = window.getTexture(_lineImage);
    textureButton = window.getTexture(_buttonImage);
    rect.w = window.getWidth() * _width;
    rect.h = texture->h * rect.w / texture->w;
    buttonRect.w = textureButton->w * rect.w / texture->w;
    buttonRect.h = textureButton->h * rect.w / texture->w;

    // Setting it to need place
    rect.x = window.getWidth() * _X - rect.w / 2;
    rect.y = window.getHeight() * _Y - rect.h / 2;
    buttonRect.y = window.getHeight() * _Y - buttonRect.h / 2;
    buttonRect.x = rect.x + rect.w * _startValue / maxValue - buttonRect.w / 2;
}

void GUI::Slider::blit() const {
    window.blit(texture, rect);
    window.blit(textureButton, buttonRect);
}

unsigned GUI::Slider::setValue(float _mouseX) {
    // Setting new position
    buttonRect.x = _mouseX;

    // Setting borders for position
    setMax(buttonRect.x, rect.x + rect.w);
    setMin(buttonRect.x, rect.x);

    unsigned value = (buttonRect.x - rect.x)*maxValue/rect.w;
    buttonRect.x -= buttonRect.w / 2;

    return value;
}

unsigned GUI::Slider::scroll(float _wheelY) {
    if (_wheelY > 0) {
        return setValue(buttonRect.x + buttonRect.w/2 + rect.w / 16);
    } else {
        return setValue(buttonRect.x + buttonRect.w/2 - rect.w / 16);
    }
    return 0;
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
