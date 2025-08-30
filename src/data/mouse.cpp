/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <SDL3/SDL_mouse.h>
#include "mouse.hpp"


Mouse::Mouse() {
    position = {0, 0};
}

void Mouse::updatePos() {
    SDL_GetMouseState(&position.x, &position.y);
}

bool Mouse::in(SDL_FRect _rect) const {
    return SDL_PointInRectFloat(&position, &_rect);
}

bool Mouse::near(float _x, float _y) const {
    return ((_x-position.x)*(_x-position.x)+(_y-position.y)*(_y-position.y)) < 25;
}

float Mouse::getX() const {
    return position.x;
}

float Mouse::getY() const {
    return position.y;
}
