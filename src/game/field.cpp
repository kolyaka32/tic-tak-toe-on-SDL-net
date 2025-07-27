/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field() {}

Field::~Field() {
    delete[] data;
}

void Field::reset() {
    for (Uint8 i=0; i < width * width; ++i) {
        data[i] = Cell::Empty;
    }
    count = 0;
    gameState = GameState::None;
}

GameState Field::getState() {
    return gameState;
}

bool Field::isWaitingStart() {
    return gameState >= GameState::CurrentWin;
}

void Field::start(GameState _player) {
    gameState = _player;
}

Cell Field::getCell(int x, int y) const {
    return data[x + y * width];
}


bool Field::clickSingle(int x, int y) {
    // Checking, if cell empty
    if (getCell(x, y) == Cell::Empty) {
        data[x + y * width] = Cell::Current;
        count++;

        // Checking for win
        gameState = checkWin(x, y);
        // Check, if need computer to play
        if (gameState < GameState::CurrentWin) {
            AImove();
        }
        return true;
    }
    return false;
}

bool Field::clickTwo(int x, int y) {
    // Checking, if turn avaliable
    if (getCell(x, y) == Cell::Empty) {
        // Setting new cell and changing player
        switch (gameState) {
        case GameState::CurrentPlay:
            data[x + y * width] = Cell::Current;
            gameState = GameState::OpponentPlay;
            break;
        
        case GameState::OpponentPlay:
            data[x + y * width] = Cell::Opponent;
            gameState = GameState::CurrentPlay;
            break;
        }
        count++;

        // Checking for win
        gameState = checkWin(x, y);
        return true;
    }
    return false;
}

bool Field::clickMultiplayerCurrent(int x, int y) {
    // Checking, if turn avaliable
    if (gameState == GameState::CurrentPlay && getCell(x, y) == Cell::Empty) {
        switch (gameState) {
        case GameState::CurrentPlay:
            data[x + y * width] = Cell::Current;
            gameState = GameState::OpponentPlay;
            break;

        case GameState::OpponentPlay:
            data[x + y * width] = Cell::Opponent;
            gameState = GameState::CurrentPlay;
            break;
        }
        count++;

        // Checking for win
        gameState = checkWin(x, y);
        return true;
    }
    return false;
}

void Field::clickMultiplayerOpponent(int x, int y) {
    if (gameState == GameState::OpponentPlay) {
        switch (gameState) {
        case GameState::CurrentPlay:
            data[x + y * width] = Cell::Current;
            gameState = GameState::OpponentPlay;
            break;

        case GameState::OpponentPlay:
            data[x + y * width] = Cell::Opponent;
            gameState = GameState::CurrentPlay;
            break;
        }
        count++;

        // Checking for win
        gameState = checkWin(x, y);
    }
}

// Recursivly solve, where cell need to be placed
int Field::recursivelySolve(Uint8 round) {
    // Look for best place to set
    int result = 0;
    for (int y=0; y < width; ++y) {
        for (int x=0; x < width; ++x) {
            if (data[y * width + x] == Cell::Empty) {
                // Trying set cell and think, what happen next
                data[y * width + x] = (Cell)(round % 2 + 1);  // Set player cell on odd rounds and enemy cell in even
                count++;
                switch (checkWin(x, y)) {
                case GameState::CurrentWin:
                    if (round % 2) {
                        result--;
                    } else{
                        result++;
                    }
                    break;
                
                case GameState::OpponentWin:
                    if (round % 2) {
                        result++;
                    } else{
                        result--;
                    }
                    break;
                case GameState::NobodyWin:  // If field already filled
                    break;
                default:
                    result -= recursivelySolve(round+1);
                };
                data[y * width + x] = Cell::Empty;
                count--;
            }
        }
    }
    return result;
}

void Field::AImove() {
    int maxScore = -127;
    int maxPos = 0;

    // Finding best place for move
    for (int i=0; i < width * width; ++i) {
        if (data[i] == Cell::Empty) {
            data[i] = Cell::Opponent;
            count++;
            int cur = recursivelySolve(1);
            if (cur > maxScore) {
                maxScore = cur;
                maxPos = i;
            }
            count--;
            data[i] = Cell::Empty;
        }
    }
    //
    data[maxPos] = Cell::Opponent;
    count++;

    // Checking for win
    gameState = checkWin(maxPos % width, maxPos / width);
}

// Return 0, if none win, 1, if win player, 2 if win bot(2 player)
GameState Field::checkWin(int X, int Y) {
    // Checking, is field full
    if (count == width * width) {
        return GameState::NobodyWin;
    }

    // Finding first starting point for X
    for (int startX = max(0, X - winWidth + 1); startX <= min(X, width - winWidth); ++startX) {
        // Checking all lines
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int x = startX; (x < startX + winWidth) && state; ++x) {
            state &= (Uint8)data[Y * width + x];
        }

        if (state) {
            return (GameState)(state+2);
        }
    }

    // Finding same first starting point for Y
    for (int startY = max(0, Y - winWidth + 1); startY <= min(Y, width - winWidth); ++startY) {
        // Checking all collumns
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int y = startY; (y < startY + winWidth) && state; ++y) {
            state &= (Uint8)data[y * width + X];
        }

        if (state) {
            return (GameState)(state+2);
        }
    }

    // Checking primal diagonal
    for (int startT = max(X - Y, 0); startT <= min(width - winWidth, width + X - Y - winWidth); ++startT) {
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int t = startT; (t < winWidth + startT) && state; ++t) {
            state &= (Uint8)data[t + (Y + t - X) * width];
        }
        if (state) {
            return (GameState)(state+2);
        }
    }

    // Checking second diagonal
    for (int startT = max(X + Y, width); startT+1 > min(winWidth, winWidth - X - Y); --startT) {
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (Sint8 t = startT; (t > startT - winWidth); --t) {
            state &= (Uint8)data[X + Y + t * (width-1)];
        }
        if (state) {
            return (GameState)(state+2);
        }
    }
    return gameState;
}

int Field::getWidth() {
    return width;
}

void Field::initWidth() {
    width = 3;
    winWidth = 3;
    data = new Cell[width * width];
}

void Field::setWidth(int _width) {
    width = _width;
    delete[] data;
    data = new Cell[width * width];
    setMin(width, 3);
    setMax(width, 9);
}

int Field::getWinWidth() {
    return winWidth;
}

void Field::setWinWidth(int _winWidth) {
    winWidth = _winWidth;
    setMin(winWidth, 3);
    setMax(winWidth, width);
}
