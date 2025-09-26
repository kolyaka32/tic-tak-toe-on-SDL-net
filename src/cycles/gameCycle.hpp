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
    Screamer screamer;

    GUI::ImageButton gameSaveButton;
    GUI::ImageButton gameMenuButton;
    GUI::StaticText playersTurnsTexts[2];
    GUI::InfoBox savedInfo;

    // Ending options
    GUI::HighlightedStaticText firstWinText;
    GUI::HighlightedStaticText secondWinText;
    GUI::HighlightedStaticText nobodyWinText;

    // New overrided cycle functions
    bool inputMouseDown() override;
    void inputKeys(const SDL_Keycode key) override;
    void update() override;

 public:
    GameCycle(Window& _window);
};
