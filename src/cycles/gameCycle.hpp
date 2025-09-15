/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/gameField.hpp"
#include "../game/startFields.hpp"
#include "../game/savedFields.hpp"
#include "../game/screamer.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    GameField field;
    StartFields startFields;
    SavedFields savedFields;
    Screamer screamer;

    const GUI::ImageButton gameMenuButton;
    GUI::StaticText playersTurnsTexts[2];

    // Menu after game end
    GUI::RoundedBackplate menuBackplate;
    GUI::TextButton menuRestartButton;
    GUI::TextButton menuStartNewButton;
    GUI::TextButton menuLoadButton;
    GUI::TextButton menuExitButton;
    // Ending options
    GUI::HighlightedStaticText firstWinText;
    GUI::HighlightedStaticText secondWinText;
    GUI::HighlightedStaticText nobodyWinText;

    // New overrided cycle functions
    bool inputMouseDown() override;
    void inputKeys(const SDL_Keycode key) override;
    void update() override;
    void draw() const override;

 public:
    GameCycle(Window& _window);
};
