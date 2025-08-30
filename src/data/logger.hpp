/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_log.h>
#include "../define.hpp"


// Function for log important information
template <typename ...Args>
void logImportant(const char* text, const Args& ...args) {
    #if (CHECK_CORRECTION)
    // Writing to stdout
    SDL_Log(text, args...);
    #endif
}

// Function for log additional information
template <typename ...Args>
void logAdditional(const char* text, const Args& ...args) {
    #if CHECK_ALL
    // Writing to stdout
    SDL_Log(text, args...);
    #endif
}
