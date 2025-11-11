/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../internet/internet.hpp"


// Cycle with game part of internet connection
class InternetCycle : public GameCycle {
 private:
    // Cycle for separated thread to get internet packets
    void internetCycle();
    IdleTimer internetTimer{1000/60};  // Timer to idle properly
    std::thread drawThread{internetCycle, this};  // Threads itself

 protected:
    // Graphical part
    GUI::StaticText playersTurnsTexts[2];
    GUI::TwoOptionBox disconnectedBox;
    GUI::OneOptionBox termianatedBox;
    GUI::HighlightedStaticText winText;
    GUI::HighlightedStaticText looseText;

    bool inputMouseDown() override;
    virtual void getInternetPacket(GetPacket& packet);

 public:
    InternetCycle(Window& window);
};
