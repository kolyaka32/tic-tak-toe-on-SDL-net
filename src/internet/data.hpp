/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/array.hpp"
#include "../codes.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include <SDL3_net/SDL_net.h>


// Function for correct bits order to prevent wrong understanding
template <typename T>
T swapLE(T object);


// Class with data for sending somewhere
class SendPacket {
 private:
    static const int maxSize = 100;
    Uint8 data[maxSize];
    Uint8* currentPosition = data;

 public:
    SendPacket();
    template <typename ...Args>
    SendPacket(const Args ...args);
    // Writing functions
    // Write multiple function
    template <typename T, typename ...Args>
    void write(const T object, const Args ...argv);
    // Write single object
    template <typename T>
    void write(const T object);
    // Write custom array
    template<typename T>
    void write(const Array<T> object);

    // Getters
    const Uint8* getData() const;
    size_t getLength() const;
};


// Class with getted data from somewhere
class GetPacket {
 private:
    // Data, contained in this array
    Uint8* data = nullptr;
    int offset = 0;
    int size;  // Size of packet for check on correction

 public:
    explicit GetPacket(NET_Datagram* datagramm);
    bool isBytesAvaliable(int bytes);
    // Functions for get data from message by order
    template <typename T>
    T getData();
    // Functions for get data from message at specified position
    template <typename T>
    T getData(int offset);
    const void* getPointer() const;
};


template <typename ...Args>
SendPacket::SendPacket(const Args ...args)
: SendPacket() {
    write(args...);
}

template <typename T>
void SendPacket::write(const T _object) {
    // Check on avaliable space
    #if (CHECK_CORRECTION)
    if (currentPosition + sizeof(T) > data + maxSize) {
        throw "Can't write data - not enogh size";
    }
    #endif
    *currentPosition = swapLE<T>(_object);
    currentPosition += sizeof(T);
}

template<typename T>
void SendPacket::write(const Array<T> _object) {
    for (int i=0; i < _object.getSize(); ++i) {
        write<T>(_object[i]);
    }
}

template <typename T, typename ...Args>
void SendPacket::write(const T _object, const Args ...args) {
    // Writing current object
    write<T>(_object);
    write(args...);
}

template <typename T>
T GetPacket::getData() {
    #if (CHECK_CORRECTION)
    if (offset + sizeof(T) > size) {
        throw "Can't read data - not enogh length";
    }
    #endif

    // Moving caret for reading next object correct
    offset += sizeof(T);
    return swapLE<T>((T)(*(data + offset - sizeof(T))));
}

template <typename T>
T GetPacket::getData(int _offset) {
    #if (CHECK_CORRECTION)
    if (_offset + sizeof(T) > size) {
        throw "Can't read data - not enogh length";
    }
    #endif
    return swapLE<T>((T)(*(data + _offset)));
}

#endif  // (USE_SDL_NET)
