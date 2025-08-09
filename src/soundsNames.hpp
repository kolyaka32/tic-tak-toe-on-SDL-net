/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/sounds.cpp"


// Names of sound effects
enum SND_names {
    // Game part
    SND_TURN,
    SND_RESET,

    // Internet connection part
    SND_DISCONNECT,

    // Screamer
    SND_SCREAMER,

    // Global counter of all loaded sounds
    SND_count,
};

// Shortcut for sounds data class
extern SoundsData<SND_count> sounds;

// File names of the corresponding sounds
extern const char* soundsFilesNames[SND_count];
