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
    CurrentPlay,
    OpponentPlay,
    CurrentWin,
    OpponentWin,
    NobodyWin,
    WaitState,
};

// Class with game field
class Field {
 private:
    // Data of field itself
    Cell data[81];        // Grid of cells, representing game field
    int count;            // Counter of filled cells
    GameState gameState;  // Current state of the game
    int offset;           // Texture offset for draw with different colors

    // Data for save/load
    SDL_Time saveTime;

    // Field window sizes
    static const float cellSide;   // Width and height of mine in pixels
    static const float separator;  // Width of separator between cells in pixels
    static const float upperLine;  // Releative height of upper line for settings (add to main)

 protected:
    Cell getCell(SDL_Point p) const;
    void setCell(SDL_Point p, Cell state);

    void checkSound();  // Function of playing sound after game end
    void AImove();      // Move of computer
    int recursivelySolve(Uint8 round);  // Function for solve game in singleplayer recursively
    GameState checkWin(SDL_Point p);    // Check, if anyone win after his turn, return who win

 public:
    // Sizes of field
    int width;     // Size of field
    int winWidth;  // Length of line to win
    float upperLinePixels;  // Absolute height of upper line in pixels

    //
    Field(int width, int winWidth);
    Field(const Field& field);
    Field& operator=(const Field* field);
    void reset();

    // Getters/setters
    GameState getState() const;
    void setState(GameState state);
    int getOffset() const;
    void setOffset(int offset);
    const char* getSaveTime() const;
    void updateSaveInfo();

    // Turns of sides
    bool clickSingle(SDL_Point p);  // Clicking in singleplayer mode
    bool clickTwo(SDL_Point p);     // Clicking in two-player mode
    bool clickMultiplayerCurrent(SDL_Point p);   // Clicking in multiplayer mode, return if have turn
    void clickMultiplayerOpponent(SDL_Point p);  // Clicking in multiplayer mode by internet connection

    // Work with graphics and sizes
    // Drawing field with his background
    void blit(const Window& window) const;
    void blitIcon(const Window& window) const;
    int getWindowWidth() const;
    int getWindowHeight() const;
    void updateWindow(Window& window);
    bool isValid(const Mouse mouse) const;
    SDL_Point getPosition(const Mouse mouse) const;
};
