/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "selectCycle.hpp"


ClientGameCycle::ClientGameCycle(const Connection& _client)
: InternetCycle(),
connection(_client),
waitText(0.5, 0.05, {"Wait start", "Ожидайте начала", "Warte auf Start", "Чаканне старту"}, 24) {
    logAdditional("Start client game cycle");
}

bool ClientGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    // Checking, if game start
    if (field.getState() >= GameState::CurrentWin) {
        // Check for game start
        if (menuExitButton.in(mouse)) {
            // Going to menu
            stop();
            return true;
        }
    } else {
        // Normal turn
        if (field.tryClickMultiplayerCurrent(mouse)) {
            // Making sound
            sounds.play(Sounds::Turn);
            music.startFromCurrent(Music::MainCombat);

            // Sending to opponent
            connection.sendConfirmed<Uint8, Uint8>(ConnectionCode::GameTurn,
                field.getXPos(mouse), field.getYPos(mouse));
        }
    }
    return false;
}

void ClientGameCycle::inputKeys(const SDL_Keycode _key) {
    // If not restart - act like normal key input
    if (_key != SDLK_R) {
        GameCycle::inputKeys(_key);
    }
}

void ClientGameCycle::update() {
    BaseCycle::update();

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        if (connection.lastPacket->isBytesAvaliable(4)) {
            logAdditional("Turn of opponent player: from %u to %u",
                connection.lastPacket->getData<Uint8>(2), connection.lastPacket->getData<Uint8>(3));
            field.clickMultiplayerOpponent(connection.lastPacket->getData<Uint8>(2),
                connection.lastPacket->getData<Uint8>(3));
            // Making sound
            sounds.play(Sounds::Turn);
            // Changing music theme
            music.startFromCurrent(Music::MainCombat);
        }
        return;

    case ConnectionCode::GameClear:
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Resetting game
        field.reset();
        logAdditional("Resetting game by connection");
        return;

    case ConnectionCode::GameStart:
        if (connection.lastPacket->isBytesAvaliable(3)) {
            logAdditional("Starting new round: %u", connection.lastPacket->getData<Uint8>(2));
            // Starting game
            switch (connection.lastPacket->getData<Uint8>(2)) {
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
            }
        }
        return;
    }
}

void ClientGameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blit();

    // Bliting game state, if need
    if (field.getState() >= GameState::CurrentWin) {
        // Bliting end background
        menuBackplate.blit();

        // Blitting buttons
        menuExitButton.blit();
    }

    // Draw game state
    switch (field.getState()) {
    case GameState::None:
        waitText.blit();
        break;

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
    }
    // Drawing buttons
    exitButton.blit();

    // Drawing setting menu
    settings.blit();

    // Messages
    disconnectedBox.blit();
    termianatedBox.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}
