/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../game/connectMenu/serverInfo.hpp"
#include "../game/connectMenu/targetConnect.hpp"


// Game cycle (for single player (special animation))
class ClientLobbyCycle : public BaseCycle {
 protected:
    // Object with all servers for connection
    std::vector<ServerData> serverDatas;
    // Socket for broadcast send data (for finding servers)
    Socket broadcastSendSocket;
    timer startSearchTimer = 0;

    // Input fields
    GUI::ScrollBox<ServerInfo, ServerData> serverScroller;
    GUI::TextButton updateButton;
    GUI::TextButton targetConnectButton;
    TargetConnect targetConnectMenu;

    void updateList();

    // Main run functions
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputText(const char* text) override;
    void update() override;
    void draw() const override;

 public:
    ClientLobbyCycle(Window& _window);
};
