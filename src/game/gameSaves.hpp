/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "field.hpp"


// Class for store all game saves and load it, when need
class GameSaves {
private:
    static std::vector<Field> startOptions;

public:
    GameSaves();
    ~GameSaves();
    static void addNewField();
    static void save();
};
