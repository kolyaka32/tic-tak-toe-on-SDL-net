#pragma once

#include "include.hpp"
#include "SDL_net.h"

enum cellTypes{
    CELL_EMPTY,
    CELL_MY,
    CELL_ENEMY
};

// Game classes
class Field
{
private:
    Uint8 *data;  // type of cell in grid from cellTypes
    Sint8 recSolve(Uint8 round);
public:
    Field(/* args */);
    ~Field();
    void reset();

    void clickSingle(Uint8 x, Uint8 y);  // Clicking in singleplayer mode
    void clickTwo(Uint8 x, Uint8 y);     // Clicking in two-player mode
    void clickMulti(Uint8 x, Uint8 y, TCPsocket sendPlace);   // Clicking inmultiplayer mode
    
    void AImove();
    int checkWin(Uint8 X, Uint8 Y);

    void blit();
};
