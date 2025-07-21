/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "coopGame.hpp"


// Two player mode (standart game)
TwoPlayerGameCycle::TwoPlayerGameCycle(const App& _app)
: GameCycle(_app) {
    if (!isRestarted()) {
        // Starting game
        field.start(GameState::CurrentPlay);
    }
}

bool TwoPlayerGameCycle::inputMouseDown(App& _app) {
    if (GameCycle::inputMouseDown(_app)) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Restarting current game
        field.reset();
        field.start(GameState::CurrentPlay);

        // Making sound
        // _app.sounds.play(SND_RESET);
        return true;
    }
    // Checking, if game start
    if (field.isWaitingStart()) {
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Restarting current game
            field.reset();
            field.start(GameState::CurrentPlay);

            // Making sound
            //_app.sounds.play(SND_RESET);
            return true;
        }
        if (menuExitButton.in(mouse)) {
            // Going to menu
            stop();
            return true;
        }
    } else {
        // Normal turn
        field.clickTwo((mouse.getX()/CELL_SIDE), (mouse.getY() - UPPER_LINE)/CELL_SIDE);
    }
    return false;
}
