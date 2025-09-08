/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "windowField.hpp"


// Static class members
const float WindowField::cellSide = 100;
const float WindowField::separator = 5;
const float WindowField::upperLineHeight = 0.1f;


WindowField::WindowField(const Window& _window)
: Template(_window),
Field() {}

WindowField::WindowField(const Field& _field, const Window& _window)
: Template(_window),
Field(_field) {}

void WindowField::blit() const {
    // Rendering cells with their background
    for (int y=0; y < width; ++y) {
        for (int x=0; x < width; ++x) {
            const SDL_FRect dest = {float(x * (cellSide + separator)),
                float(y * (cellSide + separator) + upperLineHeight), cellSide, cellSide};
            // Rendering background
            window.blit(window.getTexture(Textures::Cell), dest);

            // Rendering cells
            switch (getCell(x, y)) {
            case Cell::Current:
                window.blit(window.getTexture(Textures::GreenCross + getOffset()), dest);
                break;

            case Cell::Opponent:
                window.blit(window.getTexture(Textures::RedCircle - getOffset()), dest);
                break;

            default:
                break;
            }
        }
    }
}

int WindowField::getWidth() const {
    return width;
}

void WindowField::setWidth(int _width) {
    width = _width;
    setMin(width, 3);
    setMax(width, 9);
    setMax(winWidth, width);
}

int WindowField::getWinWidth() const {
    return winWidth;
}

void WindowField::setWinWidth(int _winWidth) {
    winWidth = _winWidth;
    setMin(winWidth, 3);
    setMax(winWidth, width);
}

int WindowField::getWindowWidth() const {
    return width * cellSide + (width - 1) * separator;
}

int WindowField::getWindowHeight() const {
    return getWindowWidth() * (1.0f + upperLineHeight);
}
