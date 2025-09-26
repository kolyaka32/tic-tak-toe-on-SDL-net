/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"
#include "../data/cycleTemplate.hpp"
#include "menu/selectingMenu.hpp"


// Creating start game field 3 by 3
Field GameField::currentField(3, 3);


GameField::GameField(const Window& _window)
: Template(_window) {}

void GameField::restart() {
    currentField.reset();
    currentField.setState(GameState::CurrentPlay);
}

GameState GameField::getState() const {
    return currentField.getState();
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

bool GameField::isGameEnd() const {
    return currentField.getState() >= GameState::CurrentWin;
}

void GameField::setNewField(const Field* field, Window& _window) {
    // Check, if need restart window
    if (currentField.width != field->width) {
        currentField = field;
        // Setting new window width, height
        currentField.updateWindow(_window);
        CycleTemplate::restart();
        CycleTemplate::stop();
    }
    currentField = field;
    // Check, if game already started
    if (currentField.isStarted()) {
        music.startFromCurrent(Music::MainCombat);
    }
}

const Field& GameField::saveField() {
    // Update save timer
    currentField.updateSaveInfo();
    return currentField;
}

const Array<char> GameField::getSave() const {
    return currentField.getSave();
}

void GameField::tryClickSingle(const Mouse _mouse) {
    if (currentField.isValid(_mouse) && currentField.getState() <= GameState::OpponentPlay) {
        currentField.clickSingle(currentField.getPosition(_mouse));
        checkEnd();
    }
}

void GameField::tryClickCoop(const Mouse _mouse) {
    if (currentField.isValid(_mouse) && currentField.getState() <= GameState::OpponentPlay) {
        currentField.clickTwo(currentField.getPosition(_mouse));
        checkEnd();
    }
}

bool GameField::tryClickServerCurrent(const Mouse _mouse) {
    if (currentField.isValid(_mouse) && currentField.getState() == GameState::CurrentPlay) {
        return currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
        checkEnd();
    }
    return false;
}

bool GameField::tryClickClientCurrent(const Mouse _mouse) {
    if (currentField.isValid(_mouse) && currentField.getState() == GameState::OpponentPlay) {
        return currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
        checkEndInverted();
    }
    return false;
}

Uint8 GameField::getLastTurn(const Mouse _mouse) {
    SDL_Point p = currentField.getPosition(_mouse);
    return p.y*currentField.width+p.x;
}

void GameField::clickServerOpponent(Uint8 _p) {
    // No additional checks for correct internet connection
    currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
    checkEnd();
}

void GameField::clickClientOpponent(Uint8 _p) {
    // No additional checks for correct internet connection
    currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
    checkEndInverted();
}

void GameField::blit() const {
    currentField.blit(window);
}

void GameField::checkEnd() {
    // Starting main combat music
    music.startFromCurrent(Music::MainCombat);
    // Making sound depend on state
    switch (currentField.getState()) {
    case GameState::CurrentWin:
        sounds.play(Sounds::Win);
        logAdditional("Opponent win");
        break;

    case GameState::OpponentWin:
        sounds.play(Sounds::Loose);
        logAdditional("Current win");
        break;

    case GameState::NobodyWin:
        sounds.play(Sounds::Loose);
        logAdditional("Nobody win");
        break;

    default:
        sounds.play(Sounds::Turn);
        return;
    }
    // Setting start menu for next game
    SelectingMenu::open();
}

void GameField::checkEndInverted() {
    // Starting main combat music
    music.startFromCurrent(Music::MainCombat);
    // Making sound depend on state
    switch (currentField.getState()) {
    case GameState::CurrentWin:
        sounds.play(Sounds::Loose);
        logAdditional("Current win");
        break;

    case GameState::OpponentWin:
        sounds.play(Sounds::Win);
        logAdditional("Opponent win");
        break;

    case GameState::NobodyWin:
        sounds.play(Sounds::Loose);
        logAdditional("Nobody win");
        break;

    default:
        sounds.play(Sounds::Turn);
        return;
    }
    // Setting start menu for next game
    SelectingMenu::open();
}
