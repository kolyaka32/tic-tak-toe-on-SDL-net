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
        #if CHECK_ALL
        SDL_Log("Start two player game");
        #endif
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
        #if CHECK_ALL
        SDL_Log("Restart game from upper button");
        #endif
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
            #if CHECK_ALL
            SDL_Log("Restart game from menu");
            #endif
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
