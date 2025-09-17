/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../internet/gameConnection.hpp"
#include "../game/menu/selectingMenu.hpp"


// Game cycle with game part of server
class ServerGameCycle : public InternetCycle {
 private:
    void sendField(const Field* field);

 protected:
    GameConnection connection;
    SelectingMenu menu;

    // Main run functions
    bool inputMouseDown() override;
    void inputKeys(SDL_Keycode key) override;
    void inputMouseWheel(float _wheelY) override;
    void update() override;
    void draw() const override;

 public:
    explicit ServerGameCycle(Window& window, const Connection& server);
};
