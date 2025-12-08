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
    #if (CHECK_ALL)
    char buffer[100];
    for (int i=0; i < _message.getLength(); ++i) {
        buffer[i] = char(_message.getData()[i] + '0');
    }
    buffer[_message.getLength()] = '\0';
    logAdditional("Sending packet to %s:%u, length %u: %s", NET_GetAddressString(address),
        port, _message.getLength(), buffer);
    #endif
    NET_SendDatagram(_sock, address, port, _message.getData(), _message.getLength());
}

const char* Destination::getName() const {
    return NET_GetAddressString(address);
}

NET_DatagramSocket* Destination::getDatagrammSocket() {
    return NET_CreateDatagramSocket(address, port);
}


StringDestination::StringDestination(const char* _address, Uint16 _port)
: Destination(NET_ResolveHostname(_address), _port) {
    // Waiting until hostname resolved
    NET_WaitUntilResolved(address, 10);
}

StringDestination::~StringDestination() {
    NET_UnrefAddress(address);
}

#endif  // (USE_SDL_NET)
