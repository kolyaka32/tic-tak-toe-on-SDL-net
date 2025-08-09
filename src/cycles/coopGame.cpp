/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "coopGame.hpp"


// Two player mode (standart game)
TwoPlayerGameCycle::TwoPlayerGameCycle()
: GameCycle() {
    if (!isRestarted()) {
        // Starting game
        field.setState(GameState::CurrentPlay);
    }
}

bool TwoPlayerGameCycle::inputMouseDown() {
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
        field.setTextureOffset(0);
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
            if (!firstTurn) {
                music.startFromCurrent(Music::MainCalm);
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
