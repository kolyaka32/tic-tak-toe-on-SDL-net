/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../game/gameMenu/selectingMenu.hpp"


// Game cycle for internet connection from server side, control client state
class ServerGameCycle : public InternetCycle {
 protected:
    SelectingMenu menu;

 protected:
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
