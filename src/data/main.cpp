/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "../cycles/selectCycle.hpp"

// Main function
int main(int argv, char **args) {
    // Running menu
    CycleTemplate::runCycle<SelectCycle>();

    // Successful end of program
    return 0;
}
