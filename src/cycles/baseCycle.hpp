/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


#include "../data/cycleTemplate.hpp"
#include "../GUI/interface.hpp"
#include "../game/settingsMenu.hpp"


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    SettingsMenu settings;     // Menu for change settings
    const GUI::ImageButton exitButton;  // Button for exit from mode

 public:
    BaseCycle(const App& app);
    bool inputMouseDown(App& app) override;
    void update(App& app) override;
    void inputMouseUp(App& app) override;
    void inputMouseWheel(App& app, float _wheelY) override;
};
