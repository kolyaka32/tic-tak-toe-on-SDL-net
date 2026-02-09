/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/gameMenu/selectingMenu.hpp"


// Game cycle (for single player (special animation))
class SinglePlayerGameCycle : public GameCycle {
 private:
    SelectingMenu menu;

 protected:
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode _key) override;
    void update() override;
    void draw() const override;

 public:
    SinglePlayerGameCycle(Window& window);
};
