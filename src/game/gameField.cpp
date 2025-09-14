/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"
#include "../data/cycleTemplate.hpp"


// Creating start game field 3 by 3
Field GameField::currentField(3, 3);


GameField::GameField(const Window& _window)
: Template(_window) {}

void GameField::restart() {
    currentField.reset();
    currentField.setOffset(0);
    currentField.setState(GameState::CurrentPlay);
}

GameState GameField::getState() const {
    return currentField.getState();
}

void GameField::setTextureOffset(int _offset) {
    currentField.setOffset(_offset);
}

void GameField::setState(GameState _state) {
    currentField.setState(_state);
}

int GameField::getWidth() {
    return currentField.width;
}

int GameField::getWindowWidth() {
    return currentField.getWindowWidth();
}

int GameField::getWindowHeight() {
    return currentField.getWindowHeight();
}

bool GameField::isGameEnd() {
    return currentField.getState() >= GameState::CurrentWin;
}

bool GameField::setNewField(const Field& field, Window& _window) {
    // Check, if need restart window
    if (currentField.width != field.width) {
        currentField = field;
        // Setting new window width, height
        _window.setWidth(currentField.getWindowWidth());
        _window.setHeight(currentField.getWindowWidth());
        CycleTemplate::restart();
        return true;
    }
    currentField = field;
    return false;
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

Uint8 GameField::getLastTurn(const Mouse _mouse) {
    SDL_Point p = currentField.getPosition(_mouse);
    return p.y*currentField.width+p.x;
}

void GameField::clickMultiplayerOpponent(Uint8 _p) {
    // No additional checks for correct internet connection
    currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
}

void GameField::blit() const {
    currentField.blit(window);
}
