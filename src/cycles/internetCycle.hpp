/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../internet/internet.hpp"


// Cycle with game part of internet connection
class InternetCycle : public GameCycle {
protected:
    // Graphical part
    GUI::StaticText playersTurnsTexts[2];
    GUI::SelectBox<2> disconnectedBox;
    GUI::SelectBox<1> termianatedBox;
    GUI::HighlightedStaticText winText;
    GUI::HighlightedStaticText looseText;

    bool inputMouseDown() override;
    void update() override;
    virtual void getInternetPacket(GetPacket& packet);

public:
    InternetCycle(Window& window);
};
