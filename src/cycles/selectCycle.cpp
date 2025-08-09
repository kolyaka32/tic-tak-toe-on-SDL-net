/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "singleplayerGame.hpp"
#include "coopGame.hpp"
#include "serverLobby.hpp"
#include "clientLobby.hpp"


// Starting basic template with main theme
SelectCycle::SelectCycle()
: BaseCycle(),
titleText(0.5, 0.15, {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}, 3, 40, WHITE),
singleplayerButton(0.5, 0.3, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}, 24, WHITE),
twoPlayerButton(0.5, 0.5, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}, 24, WHITE),
serverButton(0.5, 0.7, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}, 24, WHITE),
connectButton(0.5, 0.9, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}, 24, WHITE),
bigFieldInfobox(0.5, 0.4, {"Too big field", "Слишком большое поле", "", ""}, 24) {
    // Starting menu song (if wasn't started)
    if(!isRestarted()) {
        music.start(MUS_MENU);
    }
}

// Getting selected button
bool SelectCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (singleplayerButton.in(mouse)) {
        if (GameField::getWidth() == 3) {
            runCycle<SinglePlayerGameCycle>();
        } else {
            bigFieldInfobox.reset();
        }
        return true;
    } else if (twoPlayerButton.in(mouse)) {
        runCycle<TwoPlayerGameCycle>();
        return true;
    } else if (serverButton.in(mouse)) {
        runCycle<ServerLobbyCycle>();
        return true;
    } else if (connectButton.in(mouse)) {
        runCycle<ClientLobbyCycle>();
        return true;
    }
    return false;
}

void SelectCycle::inputKeys(SDL_Keycode _key) {
    switch (_key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;
    }
}

void SelectCycle::update() {
    BaseCycle::update();
    bigFieldInfobox.update();
}

void SelectCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Bliting title
    titleText.blit();

    // Blitting start buttons
    singleplayerButton.blit();
    twoPlayerButton.blit();
    serverButton.blit();
    connectButton.blit();

    // Settings menu
    settings.blit();

    bigFieldInfobox.blit();

    // Bliting all to screen
    window.render();
}
