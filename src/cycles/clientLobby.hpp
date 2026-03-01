/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../menu/serverInfo.hpp"
#include "../menu/targetConnect.hpp"


// Client lobby cycly for search and connect to server
class ClientLobbyCycle : public BaseCycle {
 protected:
    // Object with all servers for connection
    std::vector<ServerData> serverDatas;
    // Special socket for broadcast send data (for finding servers)
    Socket broadcastSendSocket;
    timer startSearchTimer = 0;

    // Input fields
    GUI::ScrollBox<ServerInfo, ServerData> serverScroller;
    GUI::TextButton updateButton;
    GUI::TextButton targetConnectButton;
    TargetConnect targetConnectMenu;

    // Function for reset search and start searching for new servers
    void updateList();

 protected:
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputText(const char* text) override;
    void update() override;
    void draw() const override;

 public:
    ClientLobbyCycle(Window& _window);
};
