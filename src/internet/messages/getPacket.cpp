/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "getPacket.hpp"

#if (USE_SDL_NET)


GetPacket::GetPacket(NET_Datagram* _datagram)
: datagram(_datagram) {}

GetPacket::~GetPacket() {
    // Clear rest packet
    NET_DestroyDatagram(datagram);  // ! Check on correct use
}

bool GetPacket::isBytesAvaliable(int bytes) {
    return datagram->buflen >= bytes;
}

const void* GetPacket::getPointer() const {
    return datagram->buf;
}

#endif  // (USE_SDL_NET)
