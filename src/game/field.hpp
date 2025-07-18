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
    Cell *data;           // Grid of cells, representing game field
    int count;            // Counter of filled cells
    GameState gameState;  // Current state of the game
    GameState currentPlayer;  // Code of selected player for internet connection
    static int width;     // Size of field
    static int winWidth;  // Length of line to win

protected:
    void AImove();  // Move of computer
    int recursivelySolve(Uint8 round);  // Function for solve game in singleplayer recursively
    GameState checkWin(int X, int Y);  // Check, if anyone win after his turn, return who win

public:
    // Global size of field
    static int getWidth();
    static void setWidth(int width);
    static int getWinWidth();
    static void setWinWidth(int winWidth);
    static int getWindowWidth();
    static int getWindowHeight();

    Field();
    ~Field();
    void reset();
    GameState getState();
    bool isWaitingStart();
    void start(GameState player);
    void setActivePlayer(GameState player);

    // Turns of sides
    void clickSingle(int x, int y);  // Clicking in singleplayer mode
    void clickTwo(int x, int y);     // Clicking in two-player mode
    bool clickMultiplayerCurrent(int x, int y);   // Clicking in multiplayer mode, return if have turn
    void clickMultiplayerOpponent(int x, int y);  // Clicking in multiplayer mode by internet connection

    // Drawing field with his background
    void blit(const Window& target) const;
};
