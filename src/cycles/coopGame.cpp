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
        logAdditional("Start two player game");
    }
}

bool TwoPlayerGameCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Restarting current game
        field.reset();
        field.setTextureOffset(0);
        field.setState(GameState::CurrentPlay);
        logAdditional("Restart game from upper button");
        return true;
    }
    // Checking, if game start
    if (field.getState() >= GameState::CurrentWin) {
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Making sound
            sounds.play(Sounds::Reset);
            music.startFromCurrent(Music::MainCalm);

            // Restarting current game
            field.reset();
            field.setTextureOffset(0);
            field.setState(GameState::CurrentPlay);
            logAdditional("Restart game from menu");
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
            music.startFromCurrent(Music::MainCombat);
        }
    }
    return false;
}
