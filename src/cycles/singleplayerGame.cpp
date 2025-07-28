/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "singleplayerGame.hpp"


SinglePlayerGameCycle::SinglePlayerGameCycle(App& _app)
: GameCycle(_app) {
    if(!isRestarted()) {
        // Starting game
        field.start(GameState::CurrentPlay);
        field.setTextureOffset(0);
    }
}

bool SinglePlayerGameCycle::inputMouseDown(App& _app) {
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
        field.start(GameState::CurrentPlay);
        return true;
    }
    // Checking, if game start
    if (field.isWaitingStart()) {
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Making sound
            _app.sounds.play(SND_RESET);

            // Restarting current game
            field.reset();
            field.start(GameState::CurrentPlay);
            if (!firstTurn) {
                _app.music.startFromCurrent(MUS_MAIN_CALM);
            }
            firstTurn = true;
            return true;
        }
        if (menuExitButton.in(mouse)) {
            // Going to menu
            stop();
            return true;
        }
    } else {
        // Normal turn
        if (field.tryClickSingle(mouse)) {
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

void SinglePlayerGameCycle::update(App& _app) {
    BaseCycle::update(_app);
}
