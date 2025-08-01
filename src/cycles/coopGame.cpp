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
        field.setState(GameState::CurrentPlay);
    }
}

bool TwoPlayerGameCycle::inputMouseDown(App& _app) {
    if (GameCycle::inputMouseDown(_app)) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Making sound
        _app.sounds.play(SND_RESET);

        // Restarting current game
        field.reset();
        if (!firstTurn) {
            _app.music.startFromCurrent(MUS_MAIN_CALM);
        }
        firstTurn = true;
        field.setTextureOffset(0);
        field.setState(GameState::CurrentPlay);
        return true;
    }
    // Checking, if game start
    if (field.getState() >= GameState::CurrentWin) {
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Making sound
            _app.sounds.play(SND_RESET);
            // Restarting current game
            field.reset();
            if (!firstTurn) {
                _app.music.startFromCurrent(MUS_MAIN_CALM);
            }
            firstTurn = true;
            field.setTextureOffset(0);
            field.setState(GameState::CurrentPlay);
            return true;
        }
        if (menuExitButton.in(mouse)) {
            // Going to menu
            stop();
            return true;
        }
    } else {
        // Normal turn
        if (field.tryClickTwo(mouse)) {
            // Making sound
            _app.sounds.play(SND_TURN);
            // Changing music theme
            if (firstTurn) {
                _app.music.startFromCurrent(MUS_MAIN_COMBAT);
                firstTurn = false;
            }
        }
    }
    return false;
}
