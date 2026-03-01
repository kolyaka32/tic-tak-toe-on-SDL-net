/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/gameMenu/selectingMenu.hpp"


// Local coopertive game mode
class TwoPlayerGameCycle : public GameCycle {
 protected:
   SelectingMenu menu;

 protected:
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputMouseWheel(float wheelY) override;
    void inputKeys(SDL_Keycode key) override;
    void update() override;
    void draw() const override;

 public:
    TwoPlayerGameCycle(Window& window);
};
