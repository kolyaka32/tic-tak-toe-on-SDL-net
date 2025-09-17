/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/menu/selectingMenu.hpp"


// Game cycle (for single player (special animation))
class SinglePlayerGameCycle : public GameCycle {
 private:
    SelectingMenu menu;
    // Main run functions
    bool inputMouseDown() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode _key) override;
    void draw() const override;

 public:
    SinglePlayerGameCycle(Window& window);
};
