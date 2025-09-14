/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


const float Field::cellSide = 100;
const float Field::separator = 5;
const float Field::upperLine = 0.1f;

Field::Field(int _width, int _winWidth)
: width(_width),
winWidth(_winWidth),
upperLinePixels(upperLine*getWindowWidth()) {
    reset();
}

Field::Field(const Field& _field)
: width(_field.width),
winWidth(_field.winWidth),
count(_field.count),
gameState(_field.gameState),
upperLinePixels(upperLine*getWindowWidth()) {
    memcpy(data, _field.data, sizeof(data));
}

Field& Field::operator=(const Field* _field) {
    width = _field->width;
    winWidth = _field->winWidth;
    count = _field->count;
    gameState = _field->gameState;
    upperLinePixels = upperLine*getWindowWidth();
    memcpy(data, _field->data, sizeof(data));
    return *this;
}

void Field::reset() {
    for (Uint8 i=0; i < width * width; ++i) {
        data[i] = Cell::Empty;
    }
    count = 0;
    gameState = GameState::None;
}

Cell Field::getCell(SDL_Point p) const {
    return data[p.x + p.y * width];
}

void Field::setCell(SDL_Point p, Cell _state) {
    data[p.x + p.y * width] = _state;
}

void Field::setState(GameState _state) {
    gameState = _state;
}

GameState Field::getState() const {
    return gameState;
}

int Field::getOffset() const {
    return offset;
}

void Field::setOffset(int _offset) {
    offset = _offset;
}

const std::string Field::getSaveName() const {
    return saveName;
}

const std::string Field::getSaveTime() const {
    // Creating string with date-time
    return std::to_string(saveTime.year) + '.' + std::to_string(saveTime.month)
        + '.' + std::to_string(saveTime.day) + ' ' + std::to_string(saveTime.hour)
        + ' ' + std::to_string(saveTime.minute) + ':' + std::to_string(saveTime.second);
    // ! Next need to add region date system
    // SDL_GetDateTimeLocalePreferences();
}

void Field::updateSaveInfo(const std::string _saveName) {
    saveName = _saveName;
    // Update current time
    SDL_Time time;
    SDL_GetCurrentTime(&time);
    SDL_TimeToDateTime(time, &saveTime, true);
}


bool Field::clickSingle(SDL_Point p) {
    // Checking, if cell empty
    if (getCell(p) == Cell::Empty) {
        setCell(p, Cell::Current);
        count++;

        // Checking for win
        gameState = checkWin(p);
        // Check, if need computer to play
        if (gameState < GameState::CurrentWin) {
            AImove();
        }
        checkSound();
        return true;
    }
    return false;
}

bool Field::clickTwo(SDL_Point p) {
    // Checking, if turn avaliable
    if (getCell(p) == Cell::Empty) {
        // Setting new cell and changing player
        switch (gameState) {
        case GameState::CurrentPlay:
            setCell(p, Cell::Current);
            gameState = GameState::OpponentPlay;
            break;

        case GameState::OpponentPlay:
            setCell(p, Cell::Opponent);
            gameState = GameState::CurrentPlay;
            break;

        default:
            break;
        }
        count++;

        // Checking for win
        gameState = checkWin(p);
        checkSound();
        return true;
    }
    return false;
}

bool Field::clickMultiplayerCurrent(SDL_Point p) {
    // Checking, if turn avaliable
    if (gameState == GameState::CurrentPlay && getCell(p) == Cell::Empty) {
        switch (gameState) {
        case GameState::CurrentPlay:
            setCell(p, Cell::Current);
            gameState = GameState::OpponentPlay;
            break;

        case GameState::OpponentPlay:
            setCell(p, Cell::Opponent);
            gameState = GameState::CurrentPlay;
            break;

        default:
            break;
        }
        count++;

        // Checking for win
        gameState = checkWin(p);
        checkSound();
        return true;
    }
    return false;
}

void Field::clickMultiplayerOpponent(SDL_Point p) {
    if (gameState == GameState::OpponentPlay) {
        switch (gameState) {
        case GameState::CurrentPlay:
            setCell(p, Cell::Current);
            gameState = GameState::OpponentPlay;
            break;

        case GameState::OpponentPlay:
            setCell(p, Cell::Opponent);
            gameState = GameState::CurrentPlay;
            break;

        default:
            break;
        }
        count++;

        // Checking for win
        gameState = checkWin(p);
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
                switch (checkWin({x, y})) {
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
    gameState = checkWin({maxPos % width, maxPos / width});
}

// Return 0, if none win, 1, if win player, 2 if win bot(2 player)
GameState Field::checkWin(SDL_Point p) {
    // Finding first starting point for X
    for (int startX = max(0, p.x - winWidth + 1); startX <= min(p.x, width - winWidth); ++startX) {
        // Checking all lines
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int x = startX; (x < startX + winWidth) && state; ++x) {
            state &= (Uint8)getCell({x, p.y});
        }

        if (state) {
            return (GameState)(state+2);
        }
    }

    // Finding same first starting point for Y
    for (int startY = max(0, p.y - winWidth + 1); startY <= min(p.y, width - winWidth); ++startY) {
        // Checking all collumns
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int y = startY; (y < startY + winWidth) && state; ++y) {
            state &= (Uint8)getCell({p.x, y});
        }

        if (state) {
            return (GameState)(state+2);
        }
    }

    // Checking primal diagonal
    for (int startT = max(p.x - p.y, 0); startT <= min(width - winWidth, width + p.x - p.y - winWidth); ++startT) {
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int t = startT; (t < winWidth + startT) && state; ++t) {
            state &= (Uint8)data[t + (p.y + t - p.x) * width];
        }
        if (state) {
            return (GameState)(state+2);
        }
    }

    // Checking second diagonal
    if ((width - p.y) > p.x) {
        // Upper left part
        for (int startX = max(p.x - winWidth + 1, 0); startX <= min(p.x, p.y+p.x-winWidth+1); ++startX) {
            Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

            int pos = (p.x+p.y)*width - startX * (width-1);
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
        for (int startX = max(p.x - winWidth + 1, p.x + p.y - width + 1); startX <= min(p.x, width - winWidth); ++startX) {
            Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

            int pos = (p.x+p.y)*width - startX * (width-1);
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

    default:
        break;
    }
}

void Field::blit(const Window& window) const {
    // Rendering cells with their background
    for (int y=0; y < width; ++y) {
        for (int x=0; x < width; ++x) {
            const SDL_FRect dest = {float(x * (cellSide + separator)),
                float(y * (cellSide + separator) + upperLinePixels), cellSide, cellSide};
            // Rendering background
            window.blit(window.getTexture(Textures::Cell), dest);

            // Rendering cells
            switch (getCell({x, y})) {
            case Cell::Current:
                window.blit(window.getTexture(Textures::GreenCross + getOffset()), dest);
                break;

            case Cell::Opponent:
                window.blit(window.getTexture(Textures::RedCircle - getOffset()), dest);
                break;

            default:
                break;
            }
        }
    }
}

int Field::getWindowWidth() const {
    return width * cellSide + (width - 1) * separator;
}

int Field::getWindowHeight() const {
    return getWindowWidth() * (1.0f + upperLine);
}

bool Field::isValid(const Mouse _mouse) const {
    return _mouse.getY() > upperLinePixels;
}

SDL_Point Field::getPosition(const Mouse _mouse) const {
    return {int(_mouse.getX() / (cellSide + separator)),
        int((_mouse.getY() - upperLinePixels) / (cellSide + separator))};
}
