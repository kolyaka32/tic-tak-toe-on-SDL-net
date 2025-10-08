/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../game/menu/selectingMenu.hpp"


// Game cycle with game part of server
class ServerGameCycle : public InternetCycle {
 protected:
    SelectingMenu menu;

    // Main run functions
    bool inputMouseDown() override;
    void inputKeys(SDL_Keycode key) override;
    void inputMouseWheel(float _wheelY) override;
    void getInternetPacket(GetPacket& packet) override;
    void draw() const override;

 public:
    ServerGameCycle(Window& window);
    ~ServerGameCycle();
};
