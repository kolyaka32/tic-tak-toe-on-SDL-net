/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGameCycle::ServerGameCycle(App& _app, Connection& _server)
: InternetCycle(_app),
connection(_server),
startFirst(_app.window, 0.5, 0.38, {"Start as cross", "Начать за крестик", "Am Kreuz anfangen", "Пачаць за крыжык"}, 24, WHITE),
startSecond(_app.window, 0.5, 0.49, {"Start as circle", "Начать за кружок", "Für einen Kreis beginnen", "Пачаць за гурток"}, 24, WHITE) {
    if(!isRestarted()) {
        // Sending applying initialsiation message
        connection.sendConfirmed<Uint8, Uint8>(ConnectionCode::Init, Field::getWidth(), Field::getWinWidth());
    }
}

bool ServerGameCycle::inputMouseDown(App& _app) {
    if (InternetCycle::inputMouseDown(_app)) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Clearing field
        field.reset();
        // Sending message of game clear
        connection.sendConfirmed(ConnectionCode::GameClear);
        // Making sound
        // _app.sounds.play(SND_RESET);
        return true;
    }
    // Checking, if game start
    if (field.isWaitingStart()) {
        // Check for game start
        if (startFirst.in(mouse)) {
            field.start(GameState::CurrentPlay);
            connection.sendConfirmed<Uint8>(ConnectionCode::GameStart, (Uint8)GameState::OpponentPlay);
            field.setActivePlayer(GameState::CurrentPlay);
            return true;
        }
        if (startSecond.in(mouse)) {
            field.start(GameState::OpponentPlay);
            connection.sendConfirmed<Uint8>(ConnectionCode::GameStart, (Uint8)GameState::CurrentPlay);
            field.setActivePlayer(GameState::OpponentPlay);
            return true;
        }
        if (menuExitButton.in(mouse)) {
            // Going to menu
            stop();
            return true;
        }
    } else {
        // Normal turn
        if (field.clickMultiplayerCurrent((mouse.getX()/CELL_SIDE), (mouse.getY() - UPPER_LINE)/CELL_SIDE)) {
            // Sending to opponent
            connection.sendConfirmed<Uint8, Uint8>(ConnectionCode::GameTurn, (mouse.getX()/CELL_SIDE), (mouse.getY() - UPPER_LINE)/CELL_SIDE);
        }
    }
    return false;
}

void ServerGameCycle::inputKeys(App& _app, SDL_Keycode _key) {
    if (_key == SDLK_R) {
        // Clearing field
        field.reset();
        // Sending message of game clear
        connection.sendConfirmed(ConnectionCode::GameClear);
        // Making sound
        //_app.sounds.play(SND_RESET);
        return;
    } else {
        GameCycle::inputKeys(_app, _key);
    }
}

void ServerGameCycle::update(App& _app) {
    BaseCycle::update(_app);

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        #if CHECK_CORRECTION
        SDL_Log("Turn of opponent player: from %u to %u", connection.lastPacket->getData<Uint8>(2), connection.lastPacket->getData<Uint8>(3));
        #endif
        field.clickMultiplayerOpponent(connection.lastPacket->getData<Uint8>(2), connection.lastPacket->getData<Uint8>(3));
        // Making sound
        //_app.sounds.play(SND_RESET);
        return;
    }
}

void ServerGameCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Blitting field
    field.blit(_app.window);

    // Drawing buttons
    exitButton.blit(_app.window);
    gameRestartButton.blit(_app.window);

    // Bliting waiting menu, if need
    if (field.isWaitingStart()) {
        // Bliting end background
        menuBackplate.blit(_app.window);

        // Blitting buttons
        startFirst.blit(_app.window);
        startSecond.blit(_app.window);
        menuExitButton.blit(_app.window);
    }

    // Draw game state
    switch (field.getState()) {
    case GameState::CurrentPlay:
        playersTurnsTexts[0].blit(_app.window);
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[1].blit(_app.window);
        break;

    case GameState::CurrentWin:
        firstWinText.blit(_app.window);
        break;

    case GameState::OpponentWin:
        secondWinText.blit(_app.window);
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit(_app.window);
        break;
    }
    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
