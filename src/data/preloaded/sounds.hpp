/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../soundsNames.hpp"

// Check, if use mixer and preload sounds
#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)

#include <mutex>
#include <SDL3_mixer/SDL_mixer.h>


// Class for playing sound with need name
class SoundsData {
 private:
    std::mutex mutex;
    Mix_Chunk* sounds[unsigned(Sounds::Count)];
    Uint8 volume = 0;
    void loadSound(unsigned index, const char* name);

 public:
    SoundsData();
    ~SoundsData();
    void play(Sounds name);
    void setVolume(unsigned _volume);
    unsigned getVolume() const;
};

// Global system for launch music tracks
extern SoundsData sounds;

#endif  // (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
