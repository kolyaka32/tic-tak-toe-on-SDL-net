/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_stdinc.h>


// Class for work with indexes of last get message
template <unsigned length>
class IndexesArray {
 private:
    Uint8 array[length];  // Array with last getted messages for check repeats
    int lastPosition;     // Position in array with last get message (for correct updation)

 public:
    IndexesArray();
    ~IndexesArray();
    bool isUnique(Uint8 index);
    void add(Uint8 index);
};
