/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/gameField.hpp"
#include "../game/screamer.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    GameField field;
    bool firstTurn;
    Screamer screamer;

    const GUI::ImageButton gameRestartButton;  // Button for restart game
    GUI::StaticText playersTurnsTexts[2];

    // Menu after game end
    GUI::Backplate menuBackplate;
    GUI::TextButton menuRestartButton;
    GUI::TextButton menuExitButton;
    // Ending options
    GUI::StaticText firstWinText;
    GUI::StaticText secondWinText;
    GUI::StaticText nobodyWinText;

    // New overrided cycle functions
    bool inputMouseDown(App& app) override;
    void inputKeys(App& app, const SDL_Keycode key) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    GameCycle(const App& app);
};
