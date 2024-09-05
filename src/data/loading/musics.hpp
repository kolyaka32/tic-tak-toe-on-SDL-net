/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "SDL_mixer.h"

// Class of all loaded music tracks for play
class Musics {
 private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music

    // Load track with need name
    void loadMusic(const std::string name, const MUS_names num);

    // Check correction of loaded tracks
    #if CHECK_CORRECTION
    void checkCorrection();
    #endif

 public:
    Musics();   // Load all tracks
    ~Musics();  // Clear all data
    // Play need track need times (or infinite if -1)
    void playMusic(Uint8 track, int times = -1);
};
