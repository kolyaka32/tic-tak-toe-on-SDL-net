/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "indexesArray.hpp"
#include "../data/logger.hpp"


template <unsigned length>
IndexesArray<length>::IndexesArray() {
    // Resetting array
    memset(array, 0, length);
    lastPosition = 0;
}

template <unsigned length>
IndexesArray<length>::~IndexesArray() {}

template <unsigned length>
bool IndexesArray<length>::isUnique(Uint8 _index) {
    // Check, if index in array
    for (int i=0; i < length; ++i) {
        if (array[i] == _index) {
            logAdditional("Index: %u was already get", _index);
            return false;
        }
    }
    return true;
}

template <unsigned length>
void IndexesArray<length>::add(Uint8 index) {
    // Adding new index to array, replacing older
    array[lastPosition] = index;
    // Changing caret postion to next
    lastPosition = (lastPosition + 1) % length;
}
