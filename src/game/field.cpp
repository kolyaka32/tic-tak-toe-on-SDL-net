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
saveTime(_field.saveTime),
upperLinePixels(upperLine*getWindowWidth()) {
    memcpy(data, _field.data, sizeof(data));
}

Field& Field::operator=(const Field* _field) {
    width = _field->width;
    winWidth = _field->winWidth;
    count = _field->count;
    gameState = _field->gameState;
    upperLinePixels = _field->upperLinePixels;
    saveTime = _field->saveTime;
    memcpy(data, _field->data, sizeof(data));
    return *this;
}

void Field::reset() {
    for (Uint8 i=0; i < width * width; ++i) {
        data[i] = Cell::Empty;
    }
    count = 0;
    gameState = GameState::CurrentPlay;
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

bool Field::isStarted() const {
    return count > 0;
}

const char* Field::getSaveTime() const {
    // Get time
    SDL_DateTime time;
    SDL_TimeToDateTime(saveTime, &time, true);
    // Get region specific format
    SDL_DateFormat dateFormat;
    SDL_TimeFormat timeFormat;
    SDL_GetDateTimeLocalePreferences(&dateFormat, &timeFormat);
    // Creating string with date-time
    static char buffer[22];
    // Writing date
    switch (dateFormat) {
    case SDL_DATE_FORMAT_YYYYMMDD:
        snprintf(buffer, 11, "%04d.%02d.%02d",
            time.year, time.month, time.day);
        break;

    case SDL_DATE_FORMAT_DDMMYYYY:
        snprintf(buffer, 11, "%02d.%02d.%04d",
            time.day, time.month, time.year);
        break;

    case SDL_DATE_FORMAT_MMDDYYYY:
        snprintf(buffer, 11, "%02d.%02d.%04d",
            time.year, time.month, time.day);
        break;
    }
    // Writing time
    switch (timeFormat) {
    case SDL_TIME_FORMAT_24HR:
        snprintf(buffer+10, sizeof(buffer)-10, " %02d:%02d:%02d",
            time.hour, time.minute, time.second);
        break;

    case SDL_TIME_FORMAT_12HR:
        if (time.hour < 12) {
            snprintf(buffer+10, sizeof(buffer)-10, " %02dAM:%02d:%02d",
                time.hour, time.minute, time.second);
        } else {
            snprintf(buffer+10, sizeof(buffer)-10, " %02dPM:%02d:%02d",
                time.hour, time.minute, time.second);
        }
        break;
    }
    return buffer;
}

void Field::updateSaveInfo() {
    // Update current time
    SDL_GetCurrentTime(&saveTime);
}


bool Field::clickSingle(SDL_Point p) {
    // Checking, if cell empty
    if (getCell(p) == Cell::Empty) {
        setCell(p, Cell::Current);
        count++;

        // Making sound
        sounds.play(Sounds::Turn);
        music.startFromCurrent(Music::MainCombat);

        // Checking for win
        gameState = checkWin(p);
        // Check, if need computer to play
        if (gameState < GameState::CurrentWin) {
            AImove();
        }
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
        return true;
    }
    return false;
}

bool Field::clickMultiplayerCurrent(SDL_Point p) {
    // Checking, if turn avaliable
    if (getCell(p) == Cell::Empty) {
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
        return true;
    }
    return false;
}

void Field::clickMultiplayerOpponent(SDL_Point p) {
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
    return;
}

// Recursivly solve, where cell need to be placed
int Field::recursivelySolve(Uint8 round) {
    // Check, if has too much rounds
    if (round > 3) {
        return 0;
    }
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
    int posibleCounts = 0;
    int posibleMoves[81];

    // Finding best place for move
    for (int i=0; i < width * width; ++i) {
        if (data[i] == Cell::Empty) {
            data[i] = Cell::Opponent;
            count++;
            int cur = recursivelySolve(1);
            if (cur == maxScore) {
                posibleMoves[posibleCounts] = i;
                posibleCounts++;
            }
            if (cur > maxScore) {
                maxScore = cur;
                posibleCounts = 1;
                posibleMoves[0] = i;
            }
            count--;
            data[i] = Cell::Empty;
        }
    }
    // Selecting one of posible cells (randomly)
    int move = posibleMoves[SDL_rand(posibleCounts)];
    data[move] = Cell::Opponent;
    count++;

    // Checking for win
    gameState = checkWin({move % width, move / width});
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
            return (GameState)(state+1);
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
            return (GameState)(state+1);
        }
    }

    // Checking primal diagonal
    for (int startT = max(p.x - p.y, 0); startT <= min(width - winWidth, width + p.x - p.y - winWidth); ++startT) {
        Uint8 state = (Uint8)Cell::Current | (Uint8)Cell::Opponent;

        for (int t = startT; (t < winWidth + startT) && state; ++t) {
            state &= (Uint8)data[t + (p.y + t - p.x) * width];
        }
        if (state) {
            return (GameState)(state+1);
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
                return (GameState)(state+1);
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
                return (GameState)(state+1);
            }
        }
    }
    // Checking, is field full
    if (count == width * width) {
        return GameState::NobodyWin;
    }
    return gameState;
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
                window.blit(window.getTexture(Textures::Cross), dest);
                break;

            case Cell::Opponent:
                window.blit(window.getTexture(Textures::Circle), dest);
                break;

            default:
                break;
            }
        }
    }
}

void Field::blitIcon(const Window& _window) const {
    // Rendering background
    _window.setDrawColor(BLACK);
    _window.clear();
    // Rendering cells
    for (int y=0; y < width; ++y) {
        for (int x=0; x < width; ++x) {
            const SDL_FRect dest = {float(x * (cellSide + separator)),
                float(y * (cellSide + separator)), cellSide, cellSide};
            // Rendering background
            _window.blit(_window.getTexture(Textures::Cell), dest);

            // Rendering cells
            switch (getCell({x, y})) {
            case Cell::Current:
                _window.blit(_window.getTexture(Textures::Cross), dest);
                break;

            case Cell::Opponent:
                _window.blit(_window.getTexture(Textures::Circle), dest);
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

void Field::updateWindow(Window& window) {
    window.setWidth(getWindowWidth());
    window.setHeight(getWindowHeight());
}

bool Field::isValid(const Mouse _mouse) const {
    return _mouse.getY() > upperLinePixels;
}

SDL_Point Field::getPosition(const Mouse _mouse) const {
    return {int(_mouse.getX() / (cellSide + separator)),
        int((_mouse.getY() - upperLinePixels) / (cellSide + separator))};
}

// Save system
Field::Field(const char* _saveText)
: width(_saveText[1]-'0'),
winWidth(_saveText[2]-'0'),
gameState(GameState(_saveText[3]-'0')),
upperLinePixels(upperLine*getWindowWidth()) {
    memcpy(&saveTime, _saveText+4, sizeof(saveTime));
    memcpy(data, _saveText+4+sizeof(saveTime), width*width);
}

const Array<char> Field::getSave() const {
    static char buffer[95];
    buffer[0] = getCheckSum();
    buffer[1] = width + '0';
    buffer[2] = winWidth + '0';
    buffer[3] = (char)gameState + '0';
    memcpy(buffer+4, &saveTime, sizeof(saveTime));
    // Writing data itself
    // ! should be optimised to fit better (write straight bits)
    memcpy(buffer+4+sizeof(saveTime), data, width*width);
    return Array<char>(buffer, getSaveSize(width));
}

char Field::getCheckSum() const {
    // Summing all numbers with arbitrary numbers
    int sum = saveTime + (width+1)*4 + (winWidth+3)*8;
    for (int i=0; i < width*width; ++i) {
        sum += (int)data[i];
    }
    return sum;
}

int Field::getSaveSize(int _width) {
    return 4+sizeof(saveTime)+_width*_width;
}
