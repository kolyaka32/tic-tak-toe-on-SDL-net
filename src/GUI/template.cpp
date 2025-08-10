/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


// Tempate function for resetting texture
GUI::Template::Template() {
    texture = nullptr;
}

// Template function for draw
void GUI::Template::blit() const {
    window.blit(texture, rect);
}

// Template function for check, if mouse press in object
bool GUI::Template::in(const Mouse mouse) const {
    return mouse.in(rect);
}
