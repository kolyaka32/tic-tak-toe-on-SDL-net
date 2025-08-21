/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Base cycle class
BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
exitButton(window, 0.04, 0.05, 0.08, Textures::QuitButton),
settings(window) {}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (exitButton.in(mouse)) {
        stop();
        return true;
    }
    return false;
}

void BaseCycle::update() {
    settings.update();
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
}

void BaseCycle::inputMouseWheel(float _wheelY) {
    settings.scroll(mouse, _wheelY);
}
