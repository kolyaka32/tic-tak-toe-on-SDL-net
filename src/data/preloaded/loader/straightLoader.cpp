/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "straightLoader.hpp"


// Check, if need to load data straight from files
#if (PRELOAD_DATA) && !(ARCHIEVE_LOADING)

#include "../../exceptions.hpp"


SDL_IOStream* StraightLoader::load(const char* _fileName) const {
    // Creating modified name
    size_t size = strlen(_fileName) + strlen("../") + 1;
    char* fileName = new char[size];
    snprintf(fileName, size, "../%s", _fileName);

    // Openning file straight from system
    SDL_IOStream* data = SDL_IOFromFile(fileName, "r");

    // Clearing temporary name
    delete[] fileName;

    // Checking correction of loaded font
    #if (CHECK_CORRECTION)
    if (data == nullptr) {
        throw DataLoadException(_fileName);
    }
    #endif

    return data;
}

#endif  // (PRELOAD_DATA) && !(ARCHIEVE_LOADING)
