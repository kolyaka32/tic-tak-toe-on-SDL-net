/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "field.hpp"


// Cycle with field with game objects on it
class GameField : public Field {
private:
    int offset;  // Texture offset for draw with different colors

public:
    GameField();

    // Setting texture for changing color of cells
    void setTextureOffset(int offset);

    // Getting position at grid
    int getXPos(const Mouse mouse);
    int getYPos(const Mouse mouse);

    // Game turns
    bool tryClickSingle(const Mouse mouse);  // Clicking in singleplayer mode, return if have turn
    bool tryClickTwo(const Mouse mouse);     // Clicking in two-player mode, return if have turn
    bool tryClickMultiplayerCurrent(const Mouse mouse);   // Clicking in multiplayer mode, return if have turn

    // Drawing field with his background
    void blit(const Window& target) const;
};
