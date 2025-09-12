/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"


// Creating start game field 3 by 3
Field GameField::currentField(3, 3);


GameField::GameField(const Window& _window)
: Template(_window) {}

void GameField::setNewField(const Field& field) {
    currentField = field;
}

const Field& GameField::saveField() {
    return currentField;
}

bool GameField::tryClickSingle(const Mouse _mouse) {
    if (currentField.isValid(_mouse)) {
        return currentField.clickSingle(currentField.getPosition(_mouse));
    }
    return false;
}

bool GameField::tryClickTwo(const Mouse _mouse) {
    if (currentField.isValid(_mouse)) {
        if (currentField.clickTwo(currentField.getPosition(_mouse))) {
            // Changing active player, if in game
            if (currentField.getState() <= GameState::OpponentPlay) {
                // Inversing color of active player
                currentField.setOffset(currentField.getOffset() ^ 1);
            }
            return true;
        }
    }
    return false;
}

bool GameField::tryClickMultiplayerCurrent(const Mouse _mouse) {
    if (currentField.isValid(_mouse)) {
        return currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
    }
    return false;
}

void GameField::clickMultiplayerOpponent(Uint8 x, Uint8 y) {
    // No additional checks for correct internet connection
    currentField.clickMultiplayerOpponent({x, y});
}
