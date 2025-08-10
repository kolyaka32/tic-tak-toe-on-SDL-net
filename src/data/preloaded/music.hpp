/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/loader.hpp"
#include "../../musicNames.hpp"


// Class for play music
class MusicData {
private:
    Mix_Music* music[unsigned(Music::Count)];
    Uint8 volume = 0;
    Mix_Music* currentPlay = nullptr;
    void loadMusic(Music index, const char* name);

public:
    MusicData();
    ~MusicData();
    void start(Music name);
    void startFading(Music name);
    void startFromCurrent(Music name);
    void setVolume(unsigned volume);
    unsigned getVolume() const;
};

// Global system for launch music tracks
extern MusicData music;
