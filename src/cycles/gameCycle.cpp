/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


GameCycle::GameCycle(Window& _window)
: BaseCycle(_window),
field(window),
screamer(window),
gameSaveButton(window, 0.88, 0.05, 0.08, Textures::SaveButton),
gameMenuButton(window, 0.12, 0.05, 0.08, Textures::MenuButton),
savedInfo(window, 0.5, 0.12, {"Game saved", "Игра сохранена", "Spiel gespeichert", "Гульня захавана"}),
playersTurnsTexts {
    {window, 0.5, 0.05, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}},
    {window, 0.5, 0.05, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}}
},
firstWinText(window, 0.5, 0.05, {"First win", "Первый победил", "Der erste hat gewonnen", "Першы перамог"}, 1),
secondWinText(window, 0.5, 0.05, {"Second win", "Второй победил", "Der zweite hat gewonnen", "Другі перамог"}, 1),
nobodyWinText(window, 0.5, 0.05, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 1) {
    if (!isRestarted()) {
        // Resetting field
        field.restart();
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
    // Quiting to menu
    if (key == SDLK_Q) {
        stop();
    }
}

void GameCycle::update() {
    screamer.update();
    savedInfo.update();
    BaseCycle::update();
}
