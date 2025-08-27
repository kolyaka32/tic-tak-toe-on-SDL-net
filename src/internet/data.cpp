/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data.hpp"

#if (USE_SDL_NET)


// Swap little endian function realisations
template <>
Uint8 Data::swapLE<Uint8>(Uint8 object) {
    return object;
}

template <>
Sint8 Data::swapLE<Sint8>(Sint8 object) {
    return object;
}

template <>
Uint16 Data::swapLE<Uint16>(Uint16 object) {
    return SDL_Swap16LE(object);
}

template <>
Sint16 Data::swapLE<Sint16>(Sint16 object) {
    return SDL_Swap16LE(object);
}

template <>
Uint32 Data::swapLE<Uint32>(Uint32 object) {
    return SDL_Swap32LE(object);
}

template <>
Sint32 Data::swapLE<Sint32>(Sint32 object) {
    return SDL_Swap32LE(object);
}

template <>
float Data::swapLE<float>(float object) {
    return SDL_SwapFloatLE(object);
}

template <>
Uint64 Data::swapLE<Uint64>(Uint64 object) {
    return SDL_Swap64LE(object);
}

template <>
Sint64 Data::swapLE<Sint64>(Sint64 object) {
    return SDL_Swap64LE(object);
}

// Send packet class
SendPacket::~SendPacket() {
    // Clearing rest data
    delete[] data;
}

Uint8* SendPacket::getData() const {
    return data;
}

int SendPacket::getLength() const {
    return length;
}


// Get packet class
GetPacket::GetPacket(NET_Datagram* datagramm) {
    data = datagramm->buf;
    size = datagramm->buflen;
}

bool GetPacket::isBytesAvaliable(int bytes) {
    return size >= bytes;
}

#endif  // (USE_SDL_NET)
