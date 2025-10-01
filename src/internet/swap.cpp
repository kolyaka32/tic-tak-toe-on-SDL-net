/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "swap.hpp"

#if (USE_SDL_NET)


// Swap little endian function realisations
template <>
Uint8 swapLE<Uint8>(Uint8 object) {
    return object;
}

template <>
Sint8 swapLE<Sint8>(Sint8 object) {
    return object;
}

template <>
char swapLE<char>(char object) {
    return object;
}

template <>
Uint16 swapLE<Uint16>(Uint16 object) {
    return SDL_Swap16LE(object);
}

template <>
Sint16 swapLE<Sint16>(Sint16 object) {
    return SDL_Swap16LE(object);
}

template <>
Uint32 swapLE<Uint32>(Uint32 object) {
    return SDL_Swap32LE(object);
}

template <>
Sint32 swapLE<Sint32>(Sint32 object) {
    return SDL_Swap32LE(object);
}

template <>
float swapLE<float>(float object) {
    return SDL_SwapFloatLE(object);
}

template <>
Uint64 swapLE<Uint64>(Uint64 object) {
    return SDL_Swap64LE(object);
}

template <>
Sint64 swapLE<Sint64>(Sint64 object) {
    return SDL_Swap64LE(object);
}

#endif  // (USE_SDL_NET)
