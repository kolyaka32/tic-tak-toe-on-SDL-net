/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"


// Game cycle for internet connection from client side, controlled from server
class ClientGameCycle : public InternetCycle {
 protected:
    GUI::StaticText waitText;

 protected:
    bool inputMouseDown() override;
    void getInternetPacket(const GetPacket& packet) override;
    void draw() const override;

 public:
    ClientGameCycle(Window& _window);
    ~ClientGameCycle();
};
