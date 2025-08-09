/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/loader.hpp"


// Class for playing sound with need name
template <unsigned count>
class SoundsData {
 private:
    Mix_Chunk* sounds[count];
    Uint8 volume = 0;
    void loadSound(unsigned index, const char* name);

 public:
    SoundsData(const char* names[count]);
    ~SoundsData();
    void play(unsigned name) const;
    void setVolume(unsigned _volume);
    unsigned getVolume() const;
};
