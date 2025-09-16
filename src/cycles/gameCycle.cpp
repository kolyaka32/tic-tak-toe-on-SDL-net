/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


GameCycle::GameCycle(Window& _window)
: BaseCycle(_window),
field(_window),
startFields(_window),
savedFields(_window),
screamer(window),
gameSaveButton(window, 0.88, 0.05, 0.08, Textures::SaveButton),
gameMenuButton(window, 0.12, 0.05, 0.08, Textures::MenuButton),
savedInfo(window, 0.5, 0.12, {"Game saved", "Игра сохранена", "Spiel gespeichert", "Гульня захавана"}),
playersTurnsTexts {
    {window, 0.5, 0.05, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}},
    {window, 0.5, 0.05, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}}
},
menuBackplate(window, 0.5, 0.5, 0.8, 0.7, 40, 4),
menuRestartButton(window, 0.5, 0.35, {"Restart", "Перезапустить", "Starten", "Перазапуск"}),
menuStartNewButton(window, 0.5, 0.48, {"Create new", "Создать", "Schaffen", "Стварыць"}),
menuLoadButton(window, 0.5, 0.61, {"Load", "Загрузить", "Hochladen", "Загрузіць"}),
menuExitButton(window, 0.5, 0.75, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}),
firstWinText(window, 0.5, 0.24, {"First win", "Первый победил", "Der erste hat gewonnen", "Першы перамог"}, 1, Height::Info),
secondWinText(window, 0.5, 0.24, {"Second win", "Второй победил", "Der zweite hat gewonnen", "Другі перамог"}, 1, Height::Info),
nobodyWinText(window, 0.5, 0.24, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 1, Height::Info) {
    if (!isRestarted()) {
        // Resetting field
        field.restart();
        startFields.reset();
        savedFields.reset();
    }
    // Starting main song (if wasn't started)
    music.startFading(Music::MainCalm);
}

bool GameCycle::inputMouseDown() {
    if (screamer.click(mouse)) {
        return true;
    }
    if (gameSaveButton.in(mouse)) {
        // Save current game field
        savedFields.addFieldRuntime(field.saveField());
        savedInfo.reset();
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
        field.restart();

        // Making sound
        sounds.play(Sounds::Reset);
        music.startFromCurrent(Music::MainCalm);
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
    savedInfo.update();
    BaseCycle::update();
}

void GameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blit();

    // Bliting waiting menu
    if (field.isGameEnd() || field.isWaiting()) {
        // Bliting end background
        menuBackplate.blit();

        // Blitting buttons
        menuRestartButton.blit();
        menuStartNewButton.blit();
        menuLoadButton.blit();
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
    // Blitting start variants
    startFields.blit();
    savedFields.blit();

    // Drawing upper dashboard
    exitButton.blit();
    gameMenuButton.blit();
    gameSaveButton.blit();
    savedInfo.blit();
    settings.blit();

    screamer.blit();

    // Bliting all to screen
    window.render();
}
