/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "singleplayerGame.hpp"


SinglePlayerGameCycle::SinglePlayerGameCycle()
: GameCycle() {
    if(!isRestarted()) {
        // Starting game
        field.setState(GameState::CurrentPlay);
        field.setTextureOffset(0);
    }
}

bool SinglePlayerGameCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Making sound
        sounds.play(Sounds::Reset);

        // Restarting current game
        field.reset();
        if (!firstTurn) {
            music.startFromCurrent(Music::MainCalm);
        }
        firstTurn = true;
        field.setState(GameState::CurrentPlay);
        return true;
    }
    // Checking, if game start
    if (field.getState() >= GameState::CurrentWin) {
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Making sound
            sounds.play(Sounds::Reset);

            // Restarting current game
            field.reset();
            field.setState(GameState::CurrentPlay);
            if (!firstTurn) {
                music.startFromCurrent(Music::MainCalm);
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
            sounds.play(Sounds::Turn);
            // Changing music theme
            if (firstTurn) {
                music.startFromCurrent(Music::MainCombat);
                firstTurn = false;
            }
        }
    }
    return false;
}
