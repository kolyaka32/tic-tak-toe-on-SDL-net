/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


GameCycle::GameCycle(Window& _window)
: BaseCycle(_window),
field(_window),
screamer(window),
menuRestartButton(window, 0.5, 0.5, {"Restart", "Перезапустить", "Starten", "Перазапуск"}),
menuExitButton(window, 0.5, 0.65, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}),
gameRestartButton(window, 0.12, 0.05, 0.08, Textures::RestartButton),
playersTurnsTexts {
    {window, 0.5, 0.05, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}},
    {window, 0.5, 0.05, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}}
},
menuBackplate(window, 0.5, 0.5, 1, 0.46, 40, 5),
firstWinText(window, 0.5, 0.35, {"Fist player win", "Первый игрок выйграл", "Der erste Spieler hat gewonnen", "Першы гулец выйграў"}, 1, Height::Info),
secondWinText(window, 0.5, 0.35, {"Second player win", "Второй игрок выйграл", "Der zweite Spieler hat gewonnen", "Другі гулец выйграў"}, 1, Height::Info),
nobodyWinText(window, 0.5, 0.35, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 1, Height::Info) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
    }
    // Starting main song (if wasn't started)
    music.startFading(Music::MainCalm);
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
        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);

        // Restarting game
        field.reset();
        logAdditional("Restarting game by key");
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

    default:
        break;
    }
    // Drawing setting menu
    settings.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}
