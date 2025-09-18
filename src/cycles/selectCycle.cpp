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
SelectCycle::SelectCycle(Window& _window)
: BaseCycle(_window),
titleText(window, 0.5, 0.15, {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}, 3, Height::Title),
singleplayerButton(window, 0.5, 0.3, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}),
twoPlayerButton(window, 0.5, 0.5, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}),
serverButton(window, 0.5, 0.7, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}),
connectButton(window, 0.5, 0.9, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}) {
    // Starting menu song (if wasn't started)
    music.start(Music::Menu);
    logAdditional("Start select cycle");
}

// Getting selected button
bool SelectCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (singleplayerButton.in(mouse)) {
        runCycle<SinglePlayerGameCycle>(window);
        return true;
    }
    if (twoPlayerButton.in(mouse)) {
        runCycle<TwoPlayerGameCycle>(window);
        return true;
    }
    if (serverButton.in(mouse)) {
        runCycle<ServerLobbyCycle>(window);
        return true;
    }
    if (connectButton.in(mouse)) {
        runCycle<ClientLobbyCycle>(window);
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

    // Bliting all to screen
    window.render();
}
