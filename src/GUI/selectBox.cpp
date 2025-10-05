/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


template <unsigned Count>
GUI::SelectBox<Count>::SelectBox(const Window& _window, const LanguagedText _title,
    std::array<TextButton, Count> _buttonTexts)
: Template(_window),
buttons(_buttonTexts),
mainText(_window, 0.5, 0.4, _title, 1, Height::SubTitle),
background(_window, 0.5, 0.5, 0.8, 0.5, 5.0, 1.0) {}

template <unsigned Count>
int GUI::SelectBox<Count>::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        for (int i=0; i < Count; ++i) {
            if (buttons[i].in(_mouse)) {
                return i + 1;
            }
        }
    }
    return 0;
}

template <unsigned Count>
void GUI::SelectBox<Count>::activate() {
    active = true;
}

template <unsigned Count>
void GUI::SelectBox<Count>::reset() {
    active = false;
}

template <unsigned Count>
bool GUI::SelectBox<Count>::isActive() const {
    return active;
}

template <unsigned Count>
void GUI::SelectBox<Count>::blit() const {
    if (active) {
        background.blit();
        for (int i=0; i < Count; ++i) {
            buttons[i].blit();
        }
        mainText.blit();
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
