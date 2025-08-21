/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"
// Load needed loader, depend on teting
#if ARCHIEVE_LOADING
#include "data/preloaded/loader/archieveLoader.hpp"
#else
#include "data/preloaded/loader/straightLoader.hpp"
#endif
#include "game/gameField.hpp"

// Start game cycle
#include "cycles/selectCycle.hpp"


// Static game objects
SoundsData sounds{};
MusicData music{};
Field GameField::field{};
InitFile initFile{};


// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{GameField::getWindowWidth(), GameField::getWindowHeight(),
        {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}};

    // Running menu
    CycleTemplate::runCycle<SelectCycle>(window);

    // Successful end of program
    return 0;
}
