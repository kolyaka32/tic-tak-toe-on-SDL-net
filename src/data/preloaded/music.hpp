/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/loader.hpp"


// Class for play music
template <unsigned count>
class MusicData {
 private:
    Mix_Music* music[count];
    Uint8 volume = 0;
    void loadMusic(unsigned index, const char* name);

 public:
    MusicData(const char* names[count]);
    ~MusicData();
    void start(unsigned name) const;
    void startFading(unsigned name) const;
    void startFromCurrent(unsigned name) const;
    void setVolume(unsigned volume);
    unsigned getVolume() const;
};
