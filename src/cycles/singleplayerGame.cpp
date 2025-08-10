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
        #if CHECK_ALL
        SDL_Log("Start singleplayer game");
        #endif
    }
}

bool SinglePlayerGameCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (gameRestartButton.in(mouse)) {
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Restarting current game
        field.reset();
        field.setState(GameState::CurrentPlay);
        #if CHECK_ALL
        SDL_Log("Resetting game by upper button");
        #endif
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
            music.startFromCurrent(Music::MainCalm);
            #if CHECK_ALL
            SDL_Log("Restarting game by menu button");
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
        if (field.tryClickSingle(mouse)) {
            sounds.play(Sounds::Turn);
            music.startFromCurrent(Music::MainCombat);
        }
    }
    return false;
}
