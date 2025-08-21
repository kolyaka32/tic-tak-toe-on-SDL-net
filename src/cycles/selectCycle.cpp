/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "singleplayerGame.hpp"
#include "coopGame.hpp"
#include "serverLobby.hpp"
#include "clientLobby.hpp"
#include "parametersCycle.hpp"


// Starting basic template with main theme
SelectCycle::SelectCycle(Window& _window)
: BaseCycle(_window),
titleText(window, 0.5, 0.15, {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}, 3, Height::Title),
singleplayerButton(window, 0.5, 0.3, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}),
bigFieldInfobox(window, 0.5, 0.375, {"Too big field", "Слишком большое поле", "Zu großes Feld", "Занадта вялікае поле"}),
twoPlayerButton(window, 0.5, 0.45, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}),
serverButton(window, 0.5, 0.6, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}),
connectButton(window, 0.5, 0.75, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}),
fieldParametersButton(window, 0.5, 0.9, {"Field parameters", "Параметры поля", "Feld-Parameter", "Параметры поля"}) {
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
        if (GameField::getWidth() == 3) {
            runCycle<SinglePlayerGameCycle>(window);
        } else {
            bigFieldInfobox.reset();
            logAdditional("Can't run singleplayer game (field width = %u)", GameField::getWidth());
        }
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
    if (fieldParametersButton.in(mouse)) {
        runCycle<ParametersCycle>(window);
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
    fieldParametersButton.blit();
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
