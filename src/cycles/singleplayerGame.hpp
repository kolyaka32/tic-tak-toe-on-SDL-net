/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/selectingMenu.hpp"


// Game cycle (for single player (special animation))
class SinglePlayerGameCycle : public GameCycle {
 private:
    GameMenu menu;
    // Main run functions
    bool inputMouseDown() override;
    void inputMouseWheel(float _wheelY) override;
    void draw() const override;

 public:
    SinglePlayerGameCycle(Window& window);
};
