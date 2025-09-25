/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <array>
#include "../data/array.hpp"
#include "../codes.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include <SDL3_net/SDL_net.h>


// Class with any ordered data
class Data {
 protected:
    // Data, contained in this array
    Uint8* data = nullptr;

    // Function for correct bits order to prevent wrong understanding
    template <typename T>
    T swapLE(T object);
    template <typename T>
    static size_t size(const Array<T> object);
    template <typename T>
    static size_t size(const T object);
    template <typename T, typename ...Args>
    static size_t size(const T object, const Args ...args);

 public:
    Data() {}
};


// Class with data for sending somewhere
class SendPacket : public Data {
 private:
    int length;

 protected:
    // Functions for converting data to raw array
    // Write single object
    template <typename T>
    void write(int offset, const T object);
    // Write standart array of objects
    template<typename T, size_t N>
    void write(int offset, const std::array<T, N> object);
    // Write custom array
    template<typename T>
    void write(int offset, const Array<T> object);
    // Write multiple objects
    template <typename T, typename ...Args>
    void write(int offset, const T object, const Args ...args);

 public:
    SendPacket(const void* data, int size);
    template <typename ...Args>
    SendPacket(const Args ...args);
    ~SendPacket();
    Uint8* getData() const;
    int getLength() const;
};


// Class with getted data from somewhere
class GetPacket : public Data {
 private:
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


template <typename T>
size_t Data::size(const Array<T> _object) {
    return sizeof(T)*_object.getSize();
}

template <typename T>
size_t Data::size(const T _object) {
    return sizeof(T);
}

template <typename T, typename ...Args>
size_t Data::size(const T _object, const Args ..._args) {
    return size<T>(_object) + size(_args...);
}


template <typename ...Args>
SendPacket::SendPacket(const Args ...args) {
    // Getting length as sum of all sizes of arguments
    length = size(args...);

    // Creating array for data
    data = new Uint8[length];

    write(0, args...);
}

template <typename T>
void SendPacket::write(int _offset, const T _object) {
    *(data + _offset) = swapLE<T>(_object);
}

template<typename T, size_t N>
void SendPacket::write(int _offset, const std::array<T, N> _object) {
    for (int i=0; i < N; ++i) {
        write(_offset+i*sizeof(T), _object[i]);
    }
}

template<typename T>
void SendPacket::write(int _offset, const Array<T> _object) {
    for (int i=0; i < _object.getSize(); ++i) {
        write<T>(_offset+i*sizeof(T), _object[i]);
    }
}

template <typename T, typename ...Args>
void SendPacket::write(int _offset, const T _object, const Args ...args) {
    // Writing current object
    write<T>(_offset, _object);
    write(_offset + sizeof(T), args...);
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
