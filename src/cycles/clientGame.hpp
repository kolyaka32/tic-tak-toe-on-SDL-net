/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../internet/gameConnection.hpp"


// Game cycle (for single player (special animation))
class ClientGameCycle : public InternetCycle {
 private:
    GameConnection connection;

    // Additional text
    GUI::StaticText waitText;

    // Main run functions
    bool inputMouseDown() override;
    void inputKeys(const SDL_Keycode key) override;
    void update() override;
    void draw() const override;

 public:
    explicit ClientGameCycle(const Connection& client);
};
