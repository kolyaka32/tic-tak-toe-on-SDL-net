/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/gameField.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    static GameField field;  // Main game field
    bool firstTurn;

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
    void draw(const App& app) const override;

 public:
    GameCycle(const App& app);
    static int getWidth();
    static void initWidth();
    static void setWidth(int width);
    static int getWinWidth();
    static void setWinWidth(int winWidth);
    static int getWindowWidth();
    static int getWindowHeight();
};
