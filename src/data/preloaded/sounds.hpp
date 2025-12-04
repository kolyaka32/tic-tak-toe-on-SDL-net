/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../soundsNames.hpp"

#if (PRELOAD_SOUNDS)

#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#else
#error "Can't preload sounds without library"
#endif


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

#endif  // (PRELOAD_SOUNDS)
