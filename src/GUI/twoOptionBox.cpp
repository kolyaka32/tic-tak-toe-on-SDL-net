/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::TwoOptionBox::TwoOptionBox(const Window& _window, const LanguagedText _title,
    const LanguagedText _button1Text, const LanguagedText _button2Text)
: Template(_window),
button1(_window, 0.5, 0.48, _button1Text),
button2(_window, 0.5, 0.6, _button2Text),
mainText(_window, 0.5, 0.35, _title, 1, Height::SubTitle),
background(_window, 0.5, 0.5, 0.9, 0.4, 5.0, 1.0) {}

int GUI::TwoOptionBox::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        if (button1.in(_mouse)) {
            return 2;
        }
        if (button2.in(_mouse)) {
            return 3;
        }
        return 1;
    }
    return 0;
}

void GUI::TwoOptionBox::activate() {
    active = true;
}

void GUI::TwoOptionBox::reset() {
    active = false;
}

bool GUI::TwoOptionBox::isActive() const {
    return active;
}

void GUI::TwoOptionBox::blit() const {
    if (active) {
        background.blit();
        button1.blit();
        button2.blit();
        mainText.blit();
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
