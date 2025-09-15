/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGameCycle::ServerGameCycle(Window& _window, const Connection& _server)
: InternetCycle(_window),
connection(_server) {
    if (!isRestarted()) {
        // Sending applying initialsiation message
        connection.sendConfirmed(ConnectionCode::Init);
        field.setState(GameState::None);
    }
    logAdditional("Start server game cycle");
}

bool ServerGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    if (gameMenuButton.in(mouse)) {
        // Starting menu for selecting new field
        field.setState(GameState::None);
        return true;
    }
    // Checking, if game start
    if (field.isGameEnd() || field.isWaiting()) {
        // Check, if selecting new field
        if (startFields.isActive()) {
            // Check, if select
            if (const Field* f = startFields.click(mouse)) {
                if (field.setNewField(f, window)) {
                    stop();
                }
                // Starting game
                field.setState(GameState::CurrentPlay);
                // Send that field
                sendField(f);
                // Update music
                sounds.play(Sounds::Reset);
                music.startFromCurrent(Music::MainCalm);
                logAdditional("New game from starting fields");
                return true;
            }
            return false;
        }
        // Check, if loading fields
        if (savedFields.isActive()) {
            // Check, if select
            if (const Field* f = savedFields.click(mouse)) {
                if (field.setNewField(f, window)) {
                    stop();
                }
                // Starting game
                field.setState(GameState::CurrentPlay);
                // Send that field
                sendField(f);
                // Update music
                sounds.play(Sounds::Reset);
                music.startFromCurrent(Music::MainCalm);
                logAdditional("New game from saved fields");
                return true;
            }
            return false;
        }
        // In menu checks
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Restarting current game
            field.restart();

            // Sending message
            connection.sendConfirmed(ConnectionCode::GameRestart);

            // Making sound
            sounds.play(Sounds::Reset);
            music.startFromCurrent(Music::MainCalm);
            logAdditional("Restart game from menu");
            return true;
        }
        if (menuStartNewButton.in(mouse)) {
            // Starting selecting new field from avaliable
            startFields.activate();
        }
        if (menuLoadButton.in(mouse)) {
            // Starting selecting field from previous games
            savedFields.activate();
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
        connection.sendConfirmed(ConnectionCode::GameRestart);
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Clearing field
        field.restart();
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
    if (field.isGameEnd() || field.isWaiting()) {
        // Bliting end background
        menuBackplate.blit();

        // Blitting buttons
        menuRestartButton.blit();
        menuStartNewButton.blit();
        menuLoadButton.blit();
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
    // Blitting start variants
    startFields.blit();
    savedFields.blit();

    // Drawing buttons
    exitButton.blit();
    gameMenuButton.blit();
    settings.blit();

    // Messages
    disconnectedBox.blit();
    termianatedBox.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}

void ServerGameCycle::sendField(const Field* field) {
    //connection.sendConfirmed<Uint8, Uint8>(ConnectionCode::Init, field.getWidth(), field.getWinWidth());
    // ! Need to write in correct way

    /*
    field.setState(GameState::CurrentPlay);
    connection.sendConfirmed<Uint8>(ConnectionCode::GameNew, (Uint8)GameState::OpponentPlay);
    field.setTextureOffset(0);
    logAdditional("Start game as cross (first)");
    */
}
