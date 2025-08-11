/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field()
: width(3),
winWidth(3),
count(0),
gameState(GameState::None) {}

void Field::reset() {
    for (Uint8 i=0; i < width * width; ++i) {
        data[i] = Cell::Empty;
    }
    count = 0;
    gameState = GameState::None;
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
        checkSound();
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
        checkSound();
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
        checkSound();
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
        checkSound();
        return;
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
                    } else {
                        result++;
                    }
                    break;

                case GameState::OpponentWin:
                    if (round % 2) {
                        result++;
                    } else {
                        result--;
                    }
                    break;

                case GameState::NobodyWin:  // If field already filled
                    break;

                default:
                    result -= recursivelySolve(round+1);
                }
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
    if ((width - Y) > X) {
        // Upper left part
        for (int startX = max(X - winWidth + 1, 0); startX <= min(X, Y+X-winWidth+1); ++startX) {
            Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

            int pos = (X+Y)*width - startX * (width-1);
            for (int t = 0; t < winWidth; ++t) {
                state &= (Uint8)data[pos];
                pos -= (width-1);
            }
            if (state) {
                return (GameState)(state+2);
            }
        }
    } else {
        // Bottom right part
        for (int startX = max(X - winWidth + 1, X + Y - width + 1); startX <= min(X, width - winWidth); ++startX) {
            Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

            int pos = (X+Y)*width - startX * (width-1);
            for (int t = 0; t < winWidth; ++t) {
                state &= (Uint8)data[pos];
                pos -= (width-1);
            }
            if (state) {
                return (GameState)(state+2);
            }
        }
    }
    // Checking, is field full
    if (count == width * width) {
        return GameState::NobodyWin;
    }
    return gameState;
}

void Field::checkSound() {
    switch (gameState) {
    case GameState::CurrentWin:
        sounds.play(Sounds::Win);
        logAdditional("Current win");
        break;

    case GameState::OpponentWin:
        sounds.play(Sounds::Loose);
        logAdditional("Opponent win");
        break;

    case GameState::NobodyWin:
        sounds.play(Sounds::Loose);
        logAdditional("Nobody win");
        break;
    }
}
