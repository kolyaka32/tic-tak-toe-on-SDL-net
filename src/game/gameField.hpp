/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "field.hpp"


// Cycle with field with game objects on it
class GameField : public GUI::Template {
 private:
    // Game field
    static Field currentField;

 public:
    GameField(const Window& window);

    void setNewField(const Field& field);
    const Field& saveField();

    void blit() const;

    // Game turns
    bool tryClickSingle(const Mouse mouse);  // Clicking in singleplayer mode, return if have turn
    bool tryClickTwo(const Mouse mouse);     // Clicking in two-player mode, return if have turn
    bool tryClickMultiplayerCurrent(const Mouse mouse);   // Clicking in multiplayer mode, return if have turn
    void clickMultiplayerOpponent(Uint8 x, Uint8 y);      // Clicking in multiplayer mode by internet connection
};
