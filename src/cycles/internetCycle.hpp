/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/connectionLostBox.hpp"
#include "../game/terminatedBox.hpp"


// Cycle with game part of internet connection
class InternetCycle : public GameCycle {
protected:
    // Graphical part
    GUI::StaticText playersTurnsTexts[2];
    ConnectionLostBox disconnectedBox;
    TerminatedBox termianatedBox;
    GUI::StaticText winText;
    GUI::StaticText looseText;

    bool inputMouseDown(App& app) override;

public:
    InternetCycle(const App& app);
};
