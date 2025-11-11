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
    mutex.lock();
    currentField.reset();
    currentField.setState(GameState::CurrentPlay);
    mutex.unlock();
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
    mutex.lock();
    // Check, if need restart window
    if (currentField.width != field->width) {
        currentField = field;
        // Setting new window width, height
        currentField.updateWindow(_window);
        CycleTemplate::restart();
    }
    currentField = field;
    // Check, if game already started
    if (currentField.isStarted()) {
        music.startFromCurrent(Music::MainCombat);
    }
    mutex.unlock();
}

const Field& GameField::saveField() {
    mutex.lock();
    // Update save timer
    currentField.updateSaveInfo();
    mutex.unlock();
    return currentField;
}

const Array<char> GameField::getSave() const {
    return currentField.getSave();
}

void GameField::tryClickSingle(const Mouse _mouse) {
    mutex.lock();
    if (currentField.isValid(_mouse) && currentField.getState() <= GameState::OpponentPlay) {
        currentField.clickSingle(currentField.getPosition(_mouse));
        checkEnd();
    }
    mutex.unlock();
}

void GameField::tryClickCoop(const Mouse _mouse) {
    mutex.lock();
    if (currentField.isValid(_mouse) && currentField.getState() <= GameState::OpponentPlay) {
        currentField.clickTwo(currentField.getPosition(_mouse));
        checkEnd();
    }
    mutex.unlock();
}

void GameField::tryClickServerCurrent(const Mouse _mouse) {
    mutex.lock();
    if (currentField.isValid(_mouse) && currentField.getState() == GameState::CurrentPlay) {
        currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
        checkEnd();
    }
    mutex.unlock();
}

void GameField::tryClickClientCurrent(const Mouse _mouse) {
    mutex.lock();
    if (currentField.isValid(_mouse) && currentField.getState() == GameState::OpponentPlay) {
        currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
        checkEndInverted();
    }
    mutex.unlock();
}

void GameField::clickServerOpponent(Uint8 _p) {
    mutex.lock();
    // No additional checks for correct internet connection
    currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
    checkEnd();
    mutex.unlock();
}

void GameField::clickClientOpponent(Uint8 _p) {
    mutex.lock();
    // No additional checks for correct internet connection
    currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
    checkEndInverted();
    mutex.unlock();
}

void GameField::blit() {
    mutex.lock();
    currentField.blit(window);
    mutex.unlock();
}

void GameField::checkEnd() {
    mutex.lock();
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

    mutex.unlock();
}

void GameField::checkEndInverted() {
    mutex.lock();
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

    mutex.unlock();
}
