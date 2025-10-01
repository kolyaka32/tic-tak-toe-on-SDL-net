/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "destination.hpp"


Destination::Destination(NET_Address* _address, Uint16 _port)
: address() {}

Destination::~Destination() {}

bool Destination::operator==(const Destination& b) {
    return (NET_CompareAddresses(address, b.address) == 0) && (port == b.port);
}

NET_Address* Destination::getAddress() const {
    return address;
}

Uint16 Destination::getPort() const {
    return port;
}
