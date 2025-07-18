/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../internet/gameConnection.hpp"


// Game cycle with game part of server
class ServerGameCycle : public InternetCycle {
 protected:
    GameConnection connection;

    // Starting options
    GUI::TextButton startFirst;
    GUI::TextButton startSecond;

    // Main run functions
    bool inputMouseDown(App& app) override;
    void inputKeys(App& app, SDL_Keycode key);
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ServerGameCycle(App& app, Connection& server);
};
