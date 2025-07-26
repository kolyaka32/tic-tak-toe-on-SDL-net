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
SelectCycle::SelectCycle(const App& _app)
: BaseCycle(_app),
titleText(_app.window, 0.5, 0.15, {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}, 3, 40, WHITE),
singleplayerButton(_app.window, 0.5, 0.3, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}, 24, WHITE),
twoPlayerButton(_app.window, 0.5, 0.5, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}, 24, WHITE),
serverButton(_app.window, 0.5, 0.7, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}, 24, WHITE),
connectButton(_app.window, 0.5, 0.9, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}, 24, WHITE),
bigFieldInfobox(_app.window, 0.5, 0.4, {"Too big field", "Слишком большое поле", "", ""}, 24) {
    // Starting menu song (if wasn't started)
    if(!isRestarted()) {
        // _app.music.start(MUS_MENU);
    }
}

// Getting selected button
bool SelectCycle::inputMouseDown(App& _app) {
    if (settings.click(mouse, _app)) {
        return true;
    }
    if (singleplayerButton.in(mouse)) {
        if (GameCycle::getWidth() == 3) {
            runCycle<SinglePlayerGameCycle>(_app);
        } else {
            bigFieldInfobox.reset();
        }
        return true;
    } else if (twoPlayerButton.in(mouse)) {
        runCycle<TwoPlayerGameCycle>(_app);
        return true;
    } else if (serverButton.in(mouse)) {
        runCycle<ServerLobbyCycle>(_app);
        return true;
    } else if (connectButton.in(mouse)) {
        runCycle<ClientLobbyCycle>(_app);
        return true;
    }
    return false;
}

void SelectCycle::inputKeys(App& _app, SDL_Keycode _key) {
    switch (_key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;
    }
}

void SelectCycle::update(App& _app) {
    BaseCycle::update(_app);
    bigFieldInfobox.update();
}

void SelectCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Bliting title
    titleText.blit(_app.window);

    // Blitting start buttons
    singleplayerButton.blit(_app.window);
    twoPlayerButton.blit(_app.window);
    serverButton.blit(_app.window);
    connectButton.blit(_app.window);

    // Settings menu
    settings.blit(_app.window);

    bigFieldInfobox.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
