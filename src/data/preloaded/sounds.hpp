/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/loader.hpp"
#include "../../soundsNames.hpp"


// Class for playing sound with need name
class SoundsData {
private:
    Mix_Chunk* sounds[unsigned(Sounds::Count)];
    Uint8 volume = 0;
    void loadSound(unsigned index, const char* name);

public:
    SoundsData();
    ~SoundsData();
    void play(Sounds name) const;
    void setVolume(unsigned _volume);
    unsigned getVolume() const;
};

// Global system for launch music tracks
extern SoundsData sounds;
