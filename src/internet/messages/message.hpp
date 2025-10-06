/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "swap.hpp"

// Check, if need internet library
#if (USE_SDL_NET)


// Class with data for sending somewhere
class Message {
 private:
    static const int maxSize = 100;
    Uint8 data[maxSize];
    unsigned size = 0;

 public:
    Message();
    template <typename ...Args>
    Message(const Args ...args);
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


template <typename ...Args>
Message::Message(const Args ...args)
: Message() {
    write(args...);
}

template <typename T>
void Message::write(const T _object) {
    // Check on avaliable space
    #if (CHECK_CORRECTION)
    if (size + sizeof(T) > maxSize) {
        throw "Can't write data - not enogh size";
    }
    #endif
    *(data + size) = swapLE<T>(_object);
    size += sizeof(T);
}

template<typename T>
void Message::write(const Array<T> _object) {
    for (int i=0; i < _object.getSize(); ++i) {
        write<T>(_object[i]);
    }
}

template <typename T, typename ...Args>
void Message::write(const T _object, const Args ...args) {
    // Writing current object
    write<T>(_object);
    write(args...);
}

#endif  // (USE_SDL_NET)
