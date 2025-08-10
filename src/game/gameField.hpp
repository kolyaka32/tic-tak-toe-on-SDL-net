/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "field.hpp"


// Cycle with field with game objects on it
class GameField {
 private:
    static Field field;  // Field with whole game
    static float upperLineHeight;  // Height of upper line for settings
    static int offset;   // Texture offset for draw with different colors

 public:
    void reset();
    void setState(GameState state);
    GameState getState() const;

    // Setting texture for changing color of cells
    void setTextureOffset(int offset);

    // Getting position at grid
    int getXPos(const Mouse mouse);
    int getYPos(const Mouse mouse);

    // Game turns
    bool tryClickSingle(const Mouse mouse);  // Clicking in singleplayer mode, return if have turn
    bool tryClickTwo(const Mouse mouse);     // Clicking in two-player mode, return if have turn
    bool tryClickMultiplayerCurrent(const Mouse mouse);   // Clicking in multiplayer mode, return if have turn
    void clickMultiplayerOpponent(Uint8 x, Uint8 y);      // Clicking in multiplayer mode by internet connection

    // Drawing field with his background
    void blit() const;

    // Global options to work with field
    static int getWidth();
    static void setWidth(int width);
    static int getWinWidth();
    static void setWinWidth(int winWidth);
    static int getWindowWidth();
    static int getWindowHeight();
};
