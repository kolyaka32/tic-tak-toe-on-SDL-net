/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "../game/savedFields.hpp"


ClientGameCycle::ClientGameCycle(Window& _window, const Connection& _client)
: InternetCycle(_window),
connection(_client),
waitText(window, 0.5, 0.05, {"Wait start", "Ожидайте начала", "Warte auf Start", "Чаканне старту"}) {
    if (!isRestarted()) {
        field.restart();
        field.setState(GameState::WaitState);
    }
    logAdditional("Start client game cycle");
}

bool ClientGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    if (gameSaveButton.in(mouse)) {
        // Save current game field
        SavedFields::addField(field.saveField());
        // Showing message of sucsessful saving
        savedInfo.reset();
    }
    // Normal turn
    if (field.tryClickMultiplayerCurrent(mouse)) {
        // Sending to opponent
        connection.sendConfirmed<Uint8>(ConnectionCode::GameTurn, field.getLastTurn(mouse));
    }
    return false;
}

void ClientGameCycle::update() {
    BaseCycle::update();

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        if (connection.lastPacket->isBytesAvaliable(3)) {
            field.clickMultiplayerOpponent(connection.lastPacket->getData<Uint8>(2));
            logAdditional("Turn of opponent player to %u", connection.lastPacket->getData<Uint8>(2));
        }
        return;

    case ConnectionCode::GameNew:
        if (connection.lastPacket->isBytesAvaliable(3)) {
            // Loading new field from connection
            loadField();

            // Making sound
            sounds.play(Sounds::Reset);
            music.startFromCurrent(Music::MainCalm);
            logAdditional("Resetting game by connection");
        }
        return;

    default:
        return;
    }
}

void ClientGameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blit();

    // Bliting game menu
    // menu.blit();

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

    case GameState::WaitState:
        waitText.blit();
        break;
    }
    // Drawing upper dashboard
    exitButton.blit();
    gameSaveButton.blit();
    settings.blit();

    // Messages
    savedInfo.blit();
    disconnectedBox.blit();
    termianatedBox.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}

void ClientGameCycle::loadField() {
    /*switch (connection.lastPacket->getData<Uint8>(2)) {
    case Uint8(GameState::CurrentPlay):
        field.reset();
        field.setState(GameState::CurrentPlay);
        field.setTextureOffset(1);
        break;

    case Uint8(GameState::OpponentPlay):
        field.reset();
        field.setState(GameState::OpponentPlay);
        field.setTextureOffset(0);
        break;
    }*/
    // ! Need to write in correct way
}
