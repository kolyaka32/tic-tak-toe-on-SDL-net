/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "../game/menu/savedFields.hpp"


ClientGameCycle::ClientGameCycle(Window& _window)
: InternetCycle(_window),
waitText(window, 0.5, 0.05, {"Wait start", "Ожидайте начала", "Warte auf Start", "Чаканне старту"}) {
    if (!isRestarted()) {
        field.restart();
        field.setState(GameState::WaitState);
    }
    logAdditional("Start client game cycle");
}

ClientGameCycle::~ClientGameCycle() {
    // Sending message of disconect
    internet.disconnect();
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
        logAdditional("Saving field");
    }
    // Normal turn
    if (field.tryClickClientCurrent(mouse)) {
        // Sending to opponent
        internet.sendAllConfirmed<Uint8>(ConnectionCode::GameTurn, field.getLastTurn(mouse));
    }
    return false;
}

void ClientGameCycle::getInternetPacket(GetPacket& packet) {
    // Getting internet messages
    switch (ConnectionCode(packet.getData<Uint8>())) {
    case ConnectionCode::Quit:
        termianatedBox.activate();
        break;

    case ConnectionCode::GameTurn:
        if (packet.isBytesAvaliable(3)) {
            field.clickClientOpponent(packet.getData<Uint8>(2));
            logAdditional("Turn of opponent player to %u", packet.getData<Uint8>(2));
        }
        return;

    case ConnectionCode::GameNew:
        if (packet.isBytesAvaliable(3)) {
            // Creating new field from get data
            const Field f = Field((char*)(packet.getPointer())+2);
            // Setting it as current
            field.setNewField(&f, window);

            // Making sound
            sounds.play(Sounds::Reset);
            music.startFromCurrent(Music::MainCalm);
            logAdditional("Starting new game by connection");
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
        playersTurnsTexts[1].blit();
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[0].blit();
        break;

    case GameState::CurrentWin:
        looseText.blit();
        break;

    case GameState::OpponentWin:
        winText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
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
