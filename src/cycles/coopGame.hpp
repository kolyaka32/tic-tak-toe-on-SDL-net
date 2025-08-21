/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"


// Creating two player mode (standart game)
class TwoPlayerGameCycle : public GameCycle {
 private:
    bool inputMouseDown() override;

 public:
    TwoPlayerGameCycle(Window& _window);
};
