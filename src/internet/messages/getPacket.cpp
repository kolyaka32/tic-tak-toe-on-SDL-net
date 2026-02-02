/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "getPacket.hpp"


#if (USE_WINSOCK)
GetPacket* GetPacket::tryGetData(const SOCKET _socket) {
    // Try recieve data
    srcAddressLength = sizeof(srcAddress);
    length = recvfrom(_socket, buffer, sizeof(buffer), 0, (SOCKADDR*)&srcAddress, &srcAddressLength);
    if (length > 0) {
        logAdditional("Get data with length %d: %s\n", length, buffer);
        // Reset offset
        offset = 0;
        return this;
    }
    return nullptr;
}

const sockaddr_in* GetPacket::getSourceAddress() const {
    return &srcAddress;
}

int GetPacket::getSourceAddressLength() const {
    return srcAddressLength;
}
#endif  // (USE_WINSOCK)

bool GetPacket::isBytesAvaliable(int bytes) const {
    return length >= bytes;
}

int GetPacket::getLength() const {
    return length;
}

const void* GetPacket::getPointer() const {
    return buffer;
}
