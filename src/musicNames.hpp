/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/music.cpp"


// Names of music tracks
enum MUS_names {
    // Menu part
    MUS_MENU,

    // Game part
    MUS_MAIN_CALM,
    MUS_MAIN_COMBAT,

    // Global counter of all loaded sounds
    MUS_count,
};

// Shortcut for music data class
extern MusicData<MUS_count> music;

// File names of the corresponding music
extern const char* musicFilesNames[MUS_count];
