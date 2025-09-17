/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGameCycle::ServerGameCycle(Window& _window, const Connection& _server)
: InternetCycle(_window),
connection(_server),
menu(_window) {
    if (!isRestarted()) {
        // Sending applying initialsiation message
        connection.sendConfirmed(ConnectionCode::Init);
        field.restart();
    }
    logAdditional("Start server game cycle");
}

bool ServerGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    if (gameSaveButton.in(mouse)) {
        // Save current game field
        menu.addField(field.saveField());
        // Showing message of sucsessful saving
        savedInfo.reset();
    }
    if (gameMenuButton.in(mouse)) {
        // Starting game menu
        menu.activate();
        return true;
    }
    // Checking, if game start
    if (menu.isActive()) {
        if (const Field* f = menu.click(mouse)) {
            field.setNewField(f, window);
        }
        return true;
    } else {
        // Normal turn
        if (field.tryClickMultiplayerCurrent(mouse)) {
            // Sending to opponent
            connection.sendConfirmed<Uint8>(ConnectionCode::GameTurn, field.getLastTurn(mouse));
        }
    }
    return false;
}

void ServerGameCycle::inputKeys(SDL_Keycode _key) {
    if (_key == SDLK_R) {
        // Sending message of game clear
        /*connection.sendConfirmed(ConnectionCode::GameRestart);
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Clearing field
        field.restart();
        logAdditional("Restart game by key");*/
        return;
    } else {
        GameCycle::inputKeys(_key);
    }
}

void ServerGameCycle::inputMouseWheel(float _wheelY) {
    BaseCycle::inputMouseWheel(_wheelY);
    menu.scroll(_wheelY);
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

    // Bliting waiting menu, if need
    menu.blit();

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
