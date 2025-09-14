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
    GameState getState() const;
    void setTextureOffset(int offset);
    void setState(GameState state);
    static int getWidth();
    static int getWindowWidth();
    static int getWindowHeight();

    bool isGameEnd();
    void restart();
    bool setNewField(const Field& field, Window& window);  // Return true, if need to restart cycle
    const Field& saveField();

    void blit() const override;

    // Game turns
    bool tryClickSingle(const Mouse mouse);  // Clicking in singleplayer mode, return if have turn
    bool tryClickTwo(const Mouse mouse);     // Clicking in two-player mode, return if have turn
    bool tryClickMultiplayerCurrent(const Mouse mouse);  // Clicking in multiplayer mode, return if have turn
    Uint8 getLastTurn(const Mouse mouse);                // Return last turn
    void clickMultiplayerOpponent(Uint8 position);       // Clicking in multiplayer mode by internet connection
};
