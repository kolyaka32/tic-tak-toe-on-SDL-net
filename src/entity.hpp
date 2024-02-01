#pragma once

#include "SDL_net.h"

// Types of cells on field
enum cellTypes{
    CELL_EMPTY,
    CELL_MY,
    CELL_ENEMY
};

// Game classes
class Field
{
private:
    Uint8 *data;  // Grid of cells type from cellTypes
    Sint8 recSolve(Uint8 round);  // Function for solve game in singleplayer recursivly
public:
    Field();
    ~Field();
    void reset();

    void clickSingle(Uint8 x, Uint8 y);  // Clicking in singleplayer mode
    void clickTwo(Uint8 x, Uint8 y);     // Clicking in two-player mode
    bool clickMulti(Uint8 x, Uint8 y, TCPsocket sendPlace, Uint64* timer);  // Clicking in multiplayer mode
    
    void AImove();  // Move of computer
    Uint8 checkWin(const Uint8 X, const Uint8 Y);  // Check, if anyone win after his turn, return how win or 3 if nobody

    void blit();  // Drawing field with his background
};
