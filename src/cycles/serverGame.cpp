/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGameCycle::ServerGameCycle(Window& _window, const Connection& _server)
: InternetCycle(_window),
connection(_server),
startFirst(window, 0.5, 0.45, {"Start as cross", "Начать за крестик", "Am Kreuz anfangen", "Пачаць за крыжык"}),
startSecond(window, 0.5, 0.55, {"Start as circle", "Начать за кружок", "Für einen Kreis beginnen", "Пачаць за гурток"}) {
    if (!isRestarted()) {
        // Sending applying initialsiation message
        sendField();
    }
    logAdditional("Start server game cycle");
}

bool ServerGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Sending message of game clear
        connection.sendConfirmed(ConnectionCode::GameClear);
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Clearing field
        field.reset();
        logAdditional("Restart game by upper button");
        return true;
    }
    // Checking, if game start
    if (field.getState() >= GameState::CurrentWin || field.getState() == GameState::None) {
        // Check for game start
        if (startFirst.in(mouse)) {
            field.reset();
            field.setState(GameState::CurrentPlay);
            connection.sendConfirmed<Uint8>(ConnectionCode::GameStart, (Uint8)GameState::OpponentPlay);
            field.setTextureOffset(0);
            logAdditional("Start game as cross (first)");
            return true;
        }
        if (startSecond.in(mouse)) {
            field.reset();
            field.setState(GameState::OpponentPlay);
            connection.sendConfirmed<Uint8>(ConnectionCode::GameStart, (Uint8)GameState::CurrentPlay);
            field.setTextureOffset(1);
            logAdditional("Start game as circle (second)");
            return true;
        }
        if (menuExitButton.in(mouse)) {
            // Going to menu
            stop();
            return true;
        }
    } else {
        // Normal turn
        if (field.tryClickMultiplayerCurrent(mouse)) {
            // Sending to opponent
            connection.sendConfirmed<Uint8>(ConnectionCode::GameTurn, field.getLastTurn(mouse));

            // Making sound
            sounds.play(Sounds::Turn);
            music.startFromCurrent(Music::MainCombat);
        }
    }
    return false;
}

void ServerGameCycle::inputKeys(SDL_Keycode _key) {
    if (_key == SDLK_R) {
        // Sending message of game clear
        connection.sendConfirmed(ConnectionCode::GameClear);
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Clearing field
        field.reset();
        logAdditional("Restart game by key");
        return;
    } else {
        GameCycle::inputKeys(_key);
    }
}

void ServerGameCycle::update() {
    BaseCycle::update();

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        if (connection.lastPacket->isBytesAvaliable(3)) {
            // Making turn
            field.clickMultiplayerOpponent(connection.lastPacket->getData<Uint8>(2));
            logAdditional("Turn of opponent player to %u", connection.lastPacket->getData<Uint8>(2));

            // Making sound
            sounds.play(Sounds::Turn);
            music.startFromCurrent(Music::MainCombat);
        }
        return;

    default:
        break;
    }
}

void ServerGameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blit();

    // Bliting waiting menu, if need
    if (field.getState() >= GameState::CurrentWin || field.getState() == GameState::None) {
        // Bliting end background
        menuBackplate.blit();

        // Blitting buttons
        startFirst.blit();
        startSecond.blit();
        menuExitButton.blit();
    }

    // Draw game state
    switch (field.getState()) {
    case GameState::CurrentPlay:
        playersTurnsTexts[0].blit();
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[1].blit();
        break;

    case GameState::CurrentWin:
        winText.blit();
        break;

    case GameState::OpponentWin:
        looseText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
        break;

    default:
        break;
    }
    // Drawing buttons
    exitButton.blit();
    gameRestartButton.blit();

    // Drawing setting menu
    settings.blit();

    // Messages
    disconnectedBox.blit();
    termianatedBox.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}

void ServerGameCycle::sendField() {
    // connection.sendConfirmed<Uint8, Uint8>(ConnectionCode::Init, field.getWidth(), field.getWinWidth());
    // ! Need to write in correct way
}
