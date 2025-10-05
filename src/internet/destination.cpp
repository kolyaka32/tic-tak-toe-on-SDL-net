/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "destination.hpp"

#if (USE_SDL_NET)


Destination::Destination(NET_Address* _address, Uint16 _port)
: address(_address),
port(_port) {}

bool Destination::operator==(const Destination& b) {
    return (NET_CompareAddresses(address, b.address) == 0) && (port == b.port);
}

void Destination::send(NET_DatagramSocket *_sock, const Message& _message) const {
    logAdditional("Sending packet to %s, with code %u, length %u", NET_GetAddressString(address),
        _message.getData()[0], _message.getLength());
    NET_SendDatagram(_sock, address, port, _message.getData(), _message.getLength());
}

const char* Destination::getName() const {
    return NET_GetAddressString(address);
}

#endif  // (USE_SDL_NET)
