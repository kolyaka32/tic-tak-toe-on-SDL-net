/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


// Static class members
GameField GameCycle::field;

GameCycle::GameCycle(const App& _app)
: BaseCycle(_app),
menuRestartButton(_app.window, 0.5, 0.5, {"Restart", "Перезапустить", "Starten", "Перазапуск"}, 24, WHITE),
menuExitButton(_app.window, 0.5, 0.65, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}, 24, WHITE),
gameRestartButton(_app.window, 0.15, 0.05, IMG_GUI_RESTART_BUTTON),
playersTurnsTexts {
    {_app.window, 0.5, 0.05, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}, 24, WHITE},
    {_app.window, 0.5, 0.05, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}, 24, WHITE}
},
menuBackplate(_app.window, 0.5, 0.5, 1, 0.46, 40, 5),
firstWinText(_app.window, 0.5, 0.35, {"Fist player win", "Первый игрок выйграл", "Der erste Spieler hat gewonnen", "Першы гулец выйграў"}, 30, WHITE),
secondWinText(_app.window, 0.5, 0.35, {"Second player win", "Второй игрок выйграл", "Der zweite Spieler hat gewonnen", "Другі гулец выйграў"}, 30, WHITE),
nobodyWinText(_app.window, 0.5, 0.35, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 30, WHITE) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
        firstTurn = true;
        // Starting main song (if wasn't started)
        _app.music.startFading(MUS_MAIN_CALM);
    }
}

bool GameCycle::inputMouseDown(App& _app) {
    return BaseCycle::inputMouseDown(_app);
}

void GameCycle::inputKeys(App& _app, SDL_Keycode key) {
    // Searching for key press
    switch (key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;

    case SDLK_R:
        // Restarting game
        field.reset();
        if (!firstTurn) {
            _app.music.startFromCurrent(MUS_MAIN_CALM);
        }
        firstTurn = true;
        // Making sound
        _app.sounds.play(SND_RESET);
        return;

    case SDLK_Q:
        // Quiting to menu
        stop();
        return;
    }
}

void GameCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Blitting field
    field.blit(_app.window);

    // Drawing buttons
    exitButton.blit(_app.window);
    gameRestartButton.blit(_app.window);

    // Bliting waiting menu
    if (field.isWaitingStart() || field.getState() == GameState::None) {
        // Bliting end background
        menuBackplate.blit(_app.window);

        // Blitting buttons
        menuRestartButton.blit(_app.window);
        menuExitButton.blit(_app.window);
    }

    // Draw game state
    switch (field.getState()) {
    case GameState::CurrentPlay:
        playersTurnsTexts[0].blit(_app.window);
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[1].blit(_app.window);
        break;

    case GameState::CurrentWin:
        firstWinText.blit(_app.window);
        break;

    case GameState::OpponentWin:
        secondWinText.blit(_app.window);
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit(_app.window);
        break;
    }
    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}

int GameCycle::getWidth() {
    return field.getWidth();
}

void GameCycle::initWidth() {
    field.initWidth();
}

void GameCycle::setWidth(int _width) {
    field.setWidth(_width);
}

int GameCycle::getWinWidth() {
    return field.getWinWidth();
}

void GameCycle::setWinWidth(int _winWidth) {
    field.setWinWidth(_winWidth);
}

int GameCycle::getWindowWidth() {
    return getWidth() * CELL_SIDE + (getWidth() - 1) * SEPARATOR;
}

int GameCycle::getWindowHeight() {
    return getWindowWidth() + UPPER_LINE;
}
