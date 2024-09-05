/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL.h>>

// Password for archieve (for better savete)
#define ARCHIEVE_PASSWORD NULL


// System for load any need objects from memory
// Load from file system/archieve
class DataLoader {
 protected:
    // Load object with need name
    SDL_RWops *loadObject(const std::string name);
 public:
    DataLoader();        // Initialasing system to load objects (openning archieve)
    void closeLoader();  // Closing loader after loading all
};

// Global loader for load any objects
extern DataLoader loader;
