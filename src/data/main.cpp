/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "../cycles/selectCycle.hpp"

// Global application data
App application({"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"});

// Main function
int main(int argv, char **args) {
    // Running menu
    CycleTemplate::runCycle<SelectCycle>(application);

    // Successful end of program
    return 0;
}
