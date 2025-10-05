/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "swap.hpp"

#if (USE_SDL_NET)


// Class with getted data from somewhere
class GetPacket {
 private:
    // Data, contained in this array
    NET_Datagram* datagram;
    //Uint8* data = nullptr;
    int offset = 0;
    //int size;  // Size of packet for check on correction

 public:
    explicit GetPacket(NET_Datagram* datagramm);
    ~GetPacket();
    bool isBytesAvaliable(int bytes);
    // Functions for get data from message by order
    template <typename T>
    T getData();
    // Functions for get data from message at specified position
    template <typename T>
    T getData(int offset);
    const void* getPointer() const;
};


template <typename T>
T GetPacket::getData() {
    #if (CHECK_CORRECTION)
    if (offset + sizeof(T) > datagram->buflen) {
        throw "Can't read data - not enogh length";
    }
    #endif

    // Moving caret for reading next object correct
    offset += sizeof(T);
    return swapLE<T>((T)(*(datagram->buf + offset - sizeof(T))));
}

template <typename T>
T GetPacket::getData(int _offset) {
    #if (CHECK_CORRECTION)
    if (_offset + sizeof(T) > datagram->buflen) {
        throw "Can't read data - not enogh length";
    }
    #endif
    return swapLE<T>((T)(*(datagram->buf + _offset)));
}

#endif  // (USE_SDL_NET)
