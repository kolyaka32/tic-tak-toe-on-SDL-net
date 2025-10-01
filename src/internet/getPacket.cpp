/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "getPacket.hpp"

#if (USE_SDL_NET)


GetPacket::GetPacket(NET_Datagram* datagramm) {
    data = datagramm->buf;
    size = datagramm->buflen;
}

bool GetPacket::isBytesAvaliable(int bytes) {
    return size >= bytes;
}

const void* GetPacket::getPointer() const {
    return data;
}

#endif  // (USE_SDL_NET)
