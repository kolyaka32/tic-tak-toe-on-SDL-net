/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../internet/internet.hpp"


// Cycle with game part and internet connection
class InternetCycle : public GameCycle {
 protected:
    // Messages with internet state
    GUI::TwoOptionBox disconnectedBox;
    GUI::OneOptionBox termianatedBox;

    // Redefined current texts
    GUI::StaticText playersTurnsTexts[2];
    GUI::HighlightedStaticText winText;
    GUI::HighlightedStaticText looseText;

 protected:
    bool inputMouseDown() override;
    void update() override;
    virtual void getInternetPacket(const GetPacket& packet);

 public:
    InternetCycle(Window& window);
};
