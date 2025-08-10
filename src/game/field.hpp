/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Types of cells on field
enum class Cell : Uint8 {
    Empty,
    Current,
    Opponent,
};

// Types of game state
enum class GameState : Uint8 {
    None,
    CurrentPlay,
    OpponentPlay,
    CurrentWin,
    OpponentWin,
    NobodyWin,
};

// Class with game field
class Field {
 private:
    Cell data[81];        // Grid of cells, representing game field
    int count;            // Counter of filled cells

 protected:
    void checkSound();  // Function of playing sound after game end
    void AImove();      // Move of computer
    int recursivelySolve(Uint8 round);  // Function for solve game in singleplayer recursively
    GameState checkWin(int X, int Y);  // Check, if anyone win after his turn, return who win

 public:
    // Sizes of field
    int width;     // Size of field
    int winWidth;  // Length of line to win
    // Current state of the game
    GameState gameState;

    //
    Field();
    void reset();
    Cell getCell(int x, int y) const;

    // Turns of sides
    bool clickSingle(int x, int y);  // Clicking in singleplayer mode
    bool clickTwo(int x, int y);     // Clicking in two-player mode
    bool clickMultiplayerCurrent(int x, int y);   // Clicking in multiplayer mode, return if have turn
    void clickMultiplayerOpponent(int x, int y);  // Clicking in multiplayer mode by internet connection
};
