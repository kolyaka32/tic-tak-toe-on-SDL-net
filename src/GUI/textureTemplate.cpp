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
    mutex.lock();
    rect.x += X*window.getWidth();
    rect.y += Y*window.getHeight();
    mutex.unlock();
}

// Template function for check, if mouse press in object
bool GUI::TextureTemplate::in(const Mouse mouse) const {
    return mouse.in(rect);
}

// Template function for draw
void GUI::TextureTemplate::blit() {
    mutex.lock();
    window.blit(texture, rect);
    mutex.lock();
}
