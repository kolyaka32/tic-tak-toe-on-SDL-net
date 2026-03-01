/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/gameField.hpp"
#include "../game/screamer.hpp"


// Cycle with game template with most of texts for it
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    GameField field;
    Screamer screamer;

    // Save options
    GUI::ImageButton gameSaveButton;
    GUI::ImageButton gameMenuButton;
    GUI::InfoBox savedInfo;

    // Current turn texts
    GUI::StaticText playersTurnsTexts[2];

    // Ending options
    GUI::HighlightedStaticText firstWinText;
    GUI::HighlightedStaticText secondWinText;
    GUI::HighlightedStaticText nobodyWinText;

 protected:
    bool inputMouseDown() override;
    void inputKeys(const SDL_Keycode key) override;
    void update() override;

 public:
    GameCycle(Window& window);
};
