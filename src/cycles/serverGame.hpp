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
    bool inputMouseDown() override;
    void inputKeys(SDL_Keycode key);
    void update() override;
    void draw() const override;

 public:
    ServerGameCycle(Connection& server);
};
