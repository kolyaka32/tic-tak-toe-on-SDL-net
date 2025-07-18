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
    bool inputMouseDown(App& app) override;
    void inputKeys(App& app, const SDL_Keycode key) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ClientGameCycle(App& app, Connection& client);
};
