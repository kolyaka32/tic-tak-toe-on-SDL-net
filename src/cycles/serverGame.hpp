/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../game/gameMenu/selectingMenu.hpp"


// Game cycle with game part of server
class ServerGameCycle : public InternetCycle {
 private:
    SelectingMenu menu;

 protected:
    // Main run functions
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputMouseWheel(float _wheelY) override;
    void getInternetPacket(const GetPacket& packet) override;
    void update() override;
    void draw() const override;

 public:
    ServerGameCycle(Window& window);
    ~ServerGameCycle();
};
