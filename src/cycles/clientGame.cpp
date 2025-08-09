/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "selectCycle.hpp"


ClientGameCycle::ClientGameCycle(Connection& _client)
: InternetCycle(),
connection(_client),
waitText(0.5, 0.05, {"Wait start", "Ожидайте начала", "Warte auf Start", "Чаканне старту"}, 24) {}

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
            // Sending to opponent
            connection.sendConfirmed<Uint8, Uint8>(ConnectionCode::GameTurn, field.getXPos(mouse), field.getYPos(mouse));
            // Changing music theme
            if (firstTurn) {
                music.startFromCurrent(Music::MainCombat);
                firstTurn = false;
            }
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
            #if CHECK_CORRECTION
            SDL_Log("Turn of opponent player: from %u to %u", connection.lastPacket->getData<Uint8>(2), connection.lastPacket->getData<Uint8>(3));
            #endif
            field.clickMultiplayerOpponent(connection.lastPacket->getData<Uint8>(2), connection.lastPacket->getData<Uint8>(3));
            // Making sound
            sounds.play(Sounds::Turn);
            // Changing music theme
            if (firstTurn) {
                music.startFromCurrent(Music::MainCombat);
                firstTurn = false;
            }
        }
        return;

    case ConnectionCode::GameClear:
        #if CHECK_CORRECTION
        SDL_Log("Resetting game");
        #endif
        // Resetting game
        field.reset();
        if (!firstTurn) {
            music.startFromCurrent(Music::MainCalm);
        }
        firstTurn = true;
        // Making sound
        sounds.play(Sounds::Reset);
        return;

    case ConnectionCode::GameStart:
        if (connection.lastPacket->isBytesAvaliable(3)) {
            #if CHECK_CORRECTION
            SDL_Log("Starting new round: %u", connection.lastPacket->getData<Uint8>(2));
            #endif
            // Starting game
            switch (connection.lastPacket->getData<Uint8>(2)) {
            case int(GameState::CurrentPlay):
                field.setState(GameState::CurrentPlay);
                field.setTextureOffset(1);
                break;
            
            case int(GameState::OpponentPlay):
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

    // Drawing buttons
    exitButton.blit();

    // Drawing setting menu
    settings.blit();

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
        firstWinText.blit();
        break;

    case GameState::OpponentWin:
        secondWinText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
        break;
    }
    // Messages
    disconnectedBox.blit();
    termianatedBox.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}
