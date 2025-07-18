/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/music.cpp"

// Names of music tracks
enum MUS_names{

    // Global counter of all loaded sounds
    MUS_count,
};

// Shortcut for music data class
typedef MusicData<MUS_count> Music;

// File names of the corresponding music
extern const char* musicFilesNames[MUS_count];
