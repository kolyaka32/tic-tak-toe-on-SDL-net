/*
 * Copyright (C) 2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"


// Cycle for select variants to start
class SelectCycle : public BaseCycle {
 private:
    GUI::HighlightedStaticText titleText;
    GUI::TextButton singleplayerButton;
    GUI::TextButton twoPlayerButton;
    GUI::TextButton serverButton;
    GUI::TextButton connectButton;

    // New overrided cycle functions
    bool inputMouseDown(App& app) override;
    void inputKeys(App& app, SDL_Keycode key) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    SelectCycle(const App& app);
};
