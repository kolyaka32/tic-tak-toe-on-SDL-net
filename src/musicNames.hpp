/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_MUSIC)


// Names of music tracks
enum class Music {
    // Menu part
    Menu,

    // Game part
    MainCalm,
    MainCombat,

    // Global counter of all loaded sounds
    Count,
};

// File names of the corresponding music
extern const char* musicFilesNames[unsigned(Music::Count)];

#endif  // (PRELOAD_MUSIC)
