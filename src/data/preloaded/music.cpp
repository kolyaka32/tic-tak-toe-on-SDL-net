/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "music.hpp"


MusicData::MusicData(){
    // Resetting all tracks
    #if CHECK_CORRECTION
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        music[i] = nullptr;
    }
    #endif

    // Loading all needed music tracks
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        loadMusic(Music(i), musicFilesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        if (music[i] == NULL) {
            throw DataLoadException("Music with name: " + std::string(musicFilesNames[i]));
        }
    }
    #endif

    // Resetting music volume
    setVolume(MIX_MAX_VOLUME/2);
}

MusicData::~MusicData(){
    // Closing all tracks
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        Mix_FreeMusic(music[i]);
    }
}

void MusicData::loadMusic(Music _index, const char* _name) {
    // Load data of current music track
    SDL_IOStream* iodata = dataLoader.load(_name);

    // Loading track
    music[unsigned(_index)] = Mix_LoadMUS_IO(iodata, true);

    // Checking correction of loaded track
    #if CHECK_CORRECTION
    if (music[unsigned(_index)] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif
}

void MusicData::start(Music _index) const {
    // Infinite playing selected music
    Mix_PlayMusic(music[unsigned(_index)], -1);
}

void MusicData::startFading(Music _index) const {
    // Infinite playing selected music
    Mix_FadeInMusic(music[unsigned(_index)], -1, 1000);
}

void MusicData::startFromCurrent(Music _index) const {
    // Infinite playing selected music
    double currentPos = Mix_GetMusicPosition(nullptr);
    Mix_FadeInMusicPos(music[unsigned(_index)], -1, 1000, currentPos);
}

void MusicData::setVolume(unsigned _volume) {
    // Checking correction given volume
    #if CHECK_CORRECTION
    if (_volume/2 > MIX_MAX_VOLUME) {
        throw "Wrong volume";
    }
    #endif
    volume = _volume/2;
    Mix_VolumeMusic(volume);
}

unsigned MusicData::getVolume() const {
    return volume * 2;
}
