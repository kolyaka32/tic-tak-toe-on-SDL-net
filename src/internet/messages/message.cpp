/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "message.hpp"

#if (USE_SDL_NET)


Message::Message() {}

const Uint8* Message::getData() const {
    return data;
}

size_t Message::getLength() const {
    return size;
}

void Message::write(const ConnectionCode _object) {
    // Check on avaliable space
    #if (CHECK_CORRECTION)
    if (size + sizeof(Uint8) > maxSize) {
        throw "Can't write data - not enogh size";
    }
    #endif
    *(data + size) = (Uint8)_object;
    size += sizeof(Uint8);
}

#endif  // (USE_SDL_NET)
