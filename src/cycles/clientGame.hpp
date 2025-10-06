/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"


// Game cycle (for single player (special animation))
class ClientGameCycle : public InternetCycle {
 private:
    // Additional text
    GUI::StaticText waitText;

    // Main run functions
    bool inputMouseDown() override;
    void getInternetPacket(GetPacket& packet) override;
    void draw() const override;

 public:
    ClientGameCycle(Window& _window);
    ~ClientGameCycle();
};
