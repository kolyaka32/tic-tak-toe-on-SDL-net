/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"


// Game cycle (for single player (special animation))
class SinglePlayerGameCycle : public GameCycle {
 private:
    // Main run functions
    bool inputMouseDown() override;

 public:
    SinglePlayerGameCycle(Window& window);
};
