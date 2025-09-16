/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


// Tempate function for resetting texture
GUI::TextureTemplate::TextureTemplate(const Window& _window)
: Template(_window) {
    texture = nullptr;
}

void GUI::TextureTemplate::move(float X, float Y) {
    rect.x += X*window.getWidth();
    rect.y += Y*window.getHeight();
}

// Template function for draw
void GUI::TextureTemplate::blit() const {
    window.blit(texture, rect);
}

// Template function for check, if mouse press in object
bool GUI::TextureTemplate::in(const Mouse mouse) const {
    return mouse.in(rect);
}
