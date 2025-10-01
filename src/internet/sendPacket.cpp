/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "sendPacket.hpp"

#if (USE_SDL_NET)


SendPacket::SendPacket() {}

const Uint8* SendPacket::getData() const {
    return data;
}

size_t SendPacket::getLength() const {
    return currentPosition - data;
}

#endif  // (USE_SDL_NET)
