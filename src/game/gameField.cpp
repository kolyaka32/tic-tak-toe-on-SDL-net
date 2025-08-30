/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"


// Static class members
float GameField::upperLineHeight;
int GameField::offset;
Field GameField::field{};
const float GameField::cellSide = 100;
const float GameField::separator = 5;


GameField::GameField(const Window& _window)
: Template(_window) {}

void GameField::reset() {
    field.reset();
}

void GameField::setState(GameState _state) {
    field.gameState = _state;
}

GameState GameField::getState() const {
    return field.gameState;
}

void GameField::setTextureOffset(int _state) {
    offset = _state;
}

int GameField::getXPos(const Mouse _mouse) {
    return _mouse.getX() / (cellSide + separator);
}

int GameField::getYPos(const Mouse _mouse) {
    return (_mouse.getY() - upperLineHeight) / (cellSide + separator);
}

bool GameField::tryClickSingle(const Mouse _mouse) {
    if (_mouse.getY() > upperLineHeight) {
        return field.clickSingle(getXPos(_mouse), getYPos(_mouse));
    }
    return false;
}

bool GameField::tryClickTwo(const Mouse _mouse) {
    if (_mouse.getY() > upperLineHeight) {
        if (field.clickTwo(getXPos(_mouse), getYPos(_mouse))) {
            // Changing active player, if in game
            if (field.gameState <= GameState::OpponentPlay) {
                // Inversing color of active player
                offset ^= 1;
            }
            return true;
        }
    }
    return false;
}

bool GameField::tryClickMultiplayerCurrent(const Mouse _mouse) {
    if (_mouse.getY() > upperLineHeight) {
        return field.clickMultiplayerCurrent(getXPos(_mouse), getYPos(_mouse));
    }
    return false;
}

void GameField::clickMultiplayerOpponent(Uint8 x, Uint8 y) {
    field.clickMultiplayerOpponent(x, y);
}

void GameField::blit() const {
    // Rendering cells with their background
    for (int y=0; y < field.width; ++y) {
        for (int x=0; x < field.width; ++x) {
            const SDL_FRect dest = {float(x * (cellSide + separator)),
                float(y * (cellSide + separator) + upperLineHeight), cellSide, cellSide};
            // Rendering background
            window.blit(window.getTexture(Textures::Cell), dest);

            // Rendering cells
            switch (field.getCell(x, y)) {
            case Cell::Current:
                window.blit(window.getTexture(Textures::GreenCross + offset), dest);
                break;

            case Cell::Opponent:
                window.blit(window.getTexture(Textures::RedCircle - offset), dest);
                break;

            default:
                break;
            }
        }
    }
}

int GameField::getWidth() {
    return field.width;
}

void GameField::setWidth(int _width) {
    field.width = _width;
    setMin(field.width, 3);
    setMax(field.width, 9);
    setMax(field.winWidth, field.width);
}

int GameField::getWinWidth() {
    return field.winWidth;
}

void GameField::setWinWidth(int _winWidth) {
    field.winWidth = _winWidth;
    setMin(field.winWidth, 3);
    setMax(field.winWidth, field.width);
}

int GameField::getWindowWidth() {
    int windowWidth = field.width * cellSide + (field.width - 1) * separator;
    upperLineHeight = windowWidth * 0.1;
    return windowWidth;
}

int GameField::getWindowHeight() {
    return getWindowWidth() + upperLineHeight;
}
