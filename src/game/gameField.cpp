/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"





GameField::GameField(const Window& _window)
: Template(_window) {}



int GameField::getXPos(const Mouse _mouse) {
    return _mouse.getX() / (cellSide + separator);
}

int GameField::getYPos(const Mouse _mouse) {
    return (_mouse.getY() - upperLineHeight) / (cellSide + separator);
}

bool GameField::tryClickSingle(const Mouse _mouse) {
    if (_mouse.getY() > upperLineHeight) {
        return clickSingle(getXPos(_mouse), getYPos(_mouse));
    }
    return false;
}

bool GameField::tryClickTwo(const Mouse _mouse) {
    if (_mouse.getY() > upperLineHeight) {
        if (clickTwo(getXPos(_mouse), getYPos(_mouse))) {
            // Changing active player, if in game
            if (gameState <= GameState::OpponentPlay) {
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
