/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "selectCycle.hpp"


ClientGameCycle::ClientGameCycle(App& _app, Connection& _client)
: InternetCycle(_app),
connection(_client),
waitText(_app.window, 0.5, 0.05, {"Wait start", "Ожидайте начала", "Warte auf Start", "Чаканне старту"}, 24) {
    if (!isRestarted()) {
        field.reset();
    }
}

bool ClientGameCycle::inputMouseDown(App& _app) {
    if (InternetCycle::inputMouseDown(_app)) {
        return true;
    }
    // Checking, if game start
    if (field.isWaitingStart()) {
        // Check for game start
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

void ClientGameCycle::inputKeys(App& _app, const SDL_Keycode _key) {
    // If not restart - act like normal key input
    if (_key != SDLK_R) {
        GameCycle::inputKeys(_app, _key);
    }
}

void ClientGameCycle::update(App& _app) {
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

    case ConnectionCode::GameClear:
        #if CHECK_CORRECTION
        SDL_Log("Resetting game");
        #endif
        // Resetting game
        field.reset();
        // Making sound
        // _app.sounds.play(SND_RESET);
        return;

    case ConnectionCode::GameStart:
        #if CHECK_CORRECTION
        SDL_Log("Starting new round: %u", connection.lastPacket->getData<Uint8>(2));
        #endif
        // Resetting game
        switch (connection.lastPacket->getData<Uint8>(2)) {
        case int(GameState::CurrentPlay):
            field.start(GameState::CurrentPlay);
            field.setTextureOffset(1);
            break;
        
        case int(GameState::OpponentPlay):
            field.start(GameState::OpponentPlay);
            field.setTextureOffset(0);
            break;
        }
        // Making sound
        // _app.sounds.play(SND_RESET);
        return;
    }
}

void ClientGameCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Blitting field
    field.blit(_app.window);

    // Drawing buttons
    exitButton.blit(_app.window);

    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting game state, if need
    if (field.isWaitingStart()) {
        // Bliting end background
        menuBackplate.blit(_app.window);

        // Blitting buttons
        menuExitButton.blit(_app.window);
    }

    // Draw game state
    switch (field.getState()) {
    case GameState::None:
        waitText.blit(_app.window);
        break;

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
    // Messages
    disconnectedBox.blit(_app.window);
    termianatedBox.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
