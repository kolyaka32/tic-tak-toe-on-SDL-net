/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "musicNames.hpp"

#if (PRELOAD_MUSIC)

// File names of the corresponding music
const char* musicFilesNames[unsigned(Music::Count)] = {
    // Menu part
    "mus/menu.mp3",

    // Game part
    "mus/main-calm.mp3",
    "mus/main-combat.mp3",
};

#endif  // (PRELOAD_MUSIC)
