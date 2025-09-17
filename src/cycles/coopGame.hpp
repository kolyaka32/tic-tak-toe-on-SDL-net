/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/menu/selectingMenu.hpp"


// Creating two player mode (standart game)
class TwoPlayerGameCycle : public GameCycle {
 private:
    SelectingMenu menu;
    bool inputMouseDown() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode _key) override;
    void draw() const override;

 public:
    TwoPlayerGameCycle(Window& _window);
};
