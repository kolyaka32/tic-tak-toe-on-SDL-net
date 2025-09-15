/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "singleplayerGame.hpp"


SinglePlayerGameCycle::SinglePlayerGameCycle(Window& _window)
: GameCycle(_window) {
    if (!isRestarted()) {
        // Starting game
        field.setState(GameState::None);
    }
    logAdditional("Start singleplayer game cycle");
}

bool SinglePlayerGameCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (gameMenuButton.in(mouse)) {
        // Starting menu for selecting
        field.setState(GameState::None);
        return true;
    }
    // Checking, if game start
    if (field.isGameEnd() || field.isWaiting()) {
        // Check, if selecting new field
        if (startFields.isActive()) {
            // Check, if select
            if (const Field* f = startFields.click(mouse)) {
                if (field.setNewField(f, window)) {
                    stop();
                }
                // Starting game
                field.setState(GameState::CurrentPlay);
                // Update music
                sounds.play(Sounds::Reset);
                music.startFromCurrent(Music::MainCalm);
                return true;
            }
            return false;
        }
        // Check, if loading fields
        if (savedFields.isActive()) {
            // Check, if select
            if (const Field* f = savedFields.click(mouse)) {
                if (field.setNewField(f, window)) {
                    stop();
                }
                // Starting game
                field.setState(GameState::CurrentPlay);
                // Update music
                sounds.play(Sounds::Reset);
                music.startFromCurrent(Music::MainCalm);
                return true;
            }
            return false;
        }
        // In menu checks
        // Check for game start
        if (menuRestartButton.in(mouse)) {
            // Restarting current game
            field.restart();

            // Making sound
            sounds.play(Sounds::Reset);
            music.startFromCurrent(Music::MainCalm);
            logAdditional("Restarting game by menu button");
            return true;
        }
        if (menuStartNewButton.in(mouse)) {
            // Starting selecting new field from avaliable
            startFields.activate();
        }
        if (menuLoadButton.in(mouse)) {
            // Starting selecting field from previous games
            savedFields.activate();
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
