/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"
#include "cycles/selectCycle.hpp"
#include "cycles/singleplayerGame.hpp"
#include "cycles/coopGame.hpp"
#include "cycles/serverLobby.hpp"
#include "cycles/serverGame.hpp"
#include "cycles/clientLobby.hpp"
#include "cycles/clientGame.hpp"


// Starting cycle
Cycle App::nextCycle = Cycle::Menu;

void App::run(Window& _window) {
    while (running) {
        // Selecting new
        switch (nextCycle) {
        case Cycle::Menu:
            runCycle<SelectCycle>(_window);
            break;

        case Cycle::Singleplayer:
            runCycle<SinglePlayerGameCycle>(_window);
            break;

        case Cycle::Coop:
            runCycle<TwoPlayerGameCycle>(_window);
            break;

        case Cycle::ServerLobby:
            runCycle<ServerLobbyCycle>(_window);
            break;

        case Cycle::ServerGame:
            runCycle<ServerGameCycle>(_window);
            break;

        case Cycle::ClientLobby:
            runCycle<ClientLobbyCycle>(_window);
            break;

        case Cycle::ClientGame:
            runCycle<ClientGameCycle>(_window);
            break;
        
        default:
            break;
        }
    }
}
