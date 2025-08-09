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


// Global objects
App app{};
// Selecting loader for data, depend on testing
#if ARCHIEVE_LOADING
const ArchieveLoader dataLoader{};
#else
const StraightLoader dataLoader{};
#endif

// Loaded objects
SoundsData sounds{};
MusicData music{};
Field GameField::field{};
InitFile initFile{};
Window window{GameField::getWindowWidth(), GameField::getWindowHeight(),
    {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}};
