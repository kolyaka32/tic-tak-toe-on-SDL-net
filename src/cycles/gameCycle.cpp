/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


GameCycle::GameCycle()
: BaseCycle(),
screamer(),
menuRestartButton(0.5, 0.5, {"Restart", "Перезапустить", "Starten", "Перазапуск"}, 24, WHITE),
menuExitButton(0.5, 0.65, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}, 24, WHITE),
gameRestartButton(0.12, 0.05, 0.08, IMG_GUI_RESTART_BUTTON),
playersTurnsTexts {
    {0.5, 0.05, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}, 24, WHITE},
    {0.5, 0.05, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}, 24, WHITE}
},
menuBackplate(0.5, 0.5, 1, 0.46, 40, 5),
firstWinText(0.5, 0.35, {"Fist player win", "Первый игрок выйграл", "Der erste Spieler hat gewonnen", "Першы гулец выйграў"}, 30, WHITE),
secondWinText(0.5, 0.35, {"Second player win", "Второй игрок выйграл", "Der zweite Spieler hat gewonnen", "Другі гулец выйграў"}, 30, WHITE),
nobodyWinText(0.5, 0.35, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 30, WHITE) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
        firstTurn = true;
        // Starting main song (if wasn't started)
        music.startFading(MUS_MAIN_CALM);
    }
}

bool GameCycle::inputMouseDown() {
    if (screamer.click(mouse)) {
        return true;
    }
    return BaseCycle::inputMouseDown();
}

void GameCycle::inputKeys(SDL_Keycode key) {
    // Searching for key press
    switch (key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;

    case SDLK_R:
        // Restarting game
        field.reset();
        if (!firstTurn) {
            music.startFromCurrent(MUS_MAIN_CALM);
        }
        firstTurn = true;
        // Making sound
        sounds.play(SND_RESET);
        return;

    case SDLK_Q:
        // Quiting to menu
        stop();
        return;
    }
}

void GameCycle::update() {
    screamer.update();
    BaseCycle::update();
}

void GameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blit();

    // Drawing buttons
    exitButton.blit();
    gameRestartButton.blit();

    // Bliting waiting menu
    if (field.getState() >= GameState::CurrentWin || field.getState() == GameState::None) {
        // Bliting end background
        menuBackplate.blit();

        // Blitting buttons
        menuRestartButton.blit();
        menuExitButton.blit();
    }

    // Draw game state
    switch (field.getState()) {
    case GameState::CurrentPlay:
        playersTurnsTexts[0].blit();
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[1].blit();
        break;

    case GameState::CurrentWin:
        firstWinText.blit();
        break;

    case GameState::OpponentWin:
        secondWinText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
        break;
    }
    // Drawing setting menu
    settings.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}
