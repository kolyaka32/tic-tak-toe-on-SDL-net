/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "sounds.hpp"

#if (USE_SDL_MIXER) && (PRELOAD_SOUNDS)

#include "loader/loader.hpp"
#include "../exceptions.hpp"


SoundsData::SoundsData() {
    // Resetting all sounds
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        sounds[i] = nullptr;
    }
    #endif

    // Loading all needed sounds
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        loadSound(i, soundsFilesNames[i]);
    }

    // Checking massive on loading correction
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        if (sounds[i] == NULL) {
            throw DataLoadException(soundsFilesNames[i]);
        }
    }
    logAdditional("Sounds loaded corretly");
    #endif

    // Resetting sounds volume
    setVolume(MIX_MAX_VOLUME/2);
}

SoundsData::~SoundsData() {
    // Closing all sounds
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        Mix_FreeChunk(sounds[i]);
    }
}

void SoundsData::loadSound(unsigned _index, const char* _name) {
    // Load data of current sound
    SDL_IOStream* iodata = dataLoader.load(_name);

    // Creating surface
    sounds[_index] = Mix_LoadWAV_IO(iodata, true);

    // Checking correction of loaded sound
    #if (CHECK_CORRECTION)
    if (sounds[_index] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif
}

void SoundsData::play(Sounds _index) const {
    Mix_PlayChannel(int(_index), sounds[unsigned(_index)], 0);
}

void SoundsData::setVolume(unsigned _volume) {
    // Checking correction given volume
    #if (CHECK_CORRECTION)
    if (_volume/2 > MIX_MAX_VOLUME) {
        throw "Wrong volume";
    }
    #endif
    volume = _volume/2;
    for (int i=0; i < unsigned(Sounds::Count); ++i) {
        Mix_VolumeChunk(sounds[i], volume);
    }
}

unsigned SoundsData::getVolume() const {
    return volume*2;
}

#endif  // (USE_SDL_MIXER) && (PRELOAD_SOUNDS)
