/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGameCycle::ServerGameCycle(Window& _window)
: InternetCycle(_window),
menu(_window) {
    if (!isRestarted()) {
        menu.reset();
        field.restart();
        // Sending first field
        internet.sendAllConfirmed<Array<char>>(ConnectionCode::GameNew, field.getSave());
    }
    logAdditional("Start server game cycle");
}

ServerGameCycle::~ServerGameCycle() {
    // Sending message of disconect
    internet.disconnect();
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
        logAdditional("Saving field");
    }
    if (gameMenuButton.in(mouse)) {
        // Starting game menu
        menu.activate();
        return true;
    }
    // Checking, if game start
    if (menu.isActive()) {
        if (const Field* f = menu.click(mouse)) {
            // Setting new field localy
            field.setNewField(f, window);
            // Sending it
            internet.sendAllConfirmed<Array<char>>(ConnectionCode::GameNew, field.getSave());
            menu.reset();
            logAdditional("Selecting new field");
        }
        return true;
    } else {
        // Normal turn
        if (field.tryClickServerCurrent(mouse)) {
            // Sending to opponent
            internet.sendAllConfirmed<Uint8>(ConnectionCode::GameTurn, field.getLastTurn(mouse));
        }
    }
    return false;
}

void ServerGameCycle::inputKeys(SDL_Keycode _key) {
    if (_key == SDLK_ESCAPE) {
        // Closing top open object
        if (menu.isActive()) {
            menu.escape();
        } else {
            settings.activate();
        }
        return;
    }
    GameCycle::inputKeys(_key);
}

void ServerGameCycle::inputMouseWheel(float _wheelY) {
    GameCycle::inputMouseWheel(_wheelY);
    menu.scroll(_wheelY);
}

void ServerGameCycle::getInternetPacket(GetPacket& packet) {
    // Getting internet messages
    switch (ConnectionCode(packet.getData<Uint8>())) {
    case ConnectionCode::Quit:
        termianatedBox.activate();
        break;

    case ConnectionCode::GameTurn:
        if (packet.isBytesAvaliable(3)) {
            // Making turn
            field.clickServerOpponent(packet.getData<Uint8>(2));

            // Making sound
            sounds.play(Sounds::Turn);
            music.startFromCurrent(Music::MainCombat);
            logAdditional("Turn of opponent player to %u", packet.getData<Uint8>(2));
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
        firstWinText.blit();
        break;

    case GameState::OpponentWin:
        secondWinText.blit();
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
    gameSaveButton.blit();
    gameMenuButton.blit();
    settings.blit();

    // Messages
    savedInfo.blit();
    disconnectedBox.blit();
    termianatedBox.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}
