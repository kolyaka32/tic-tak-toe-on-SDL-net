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

void Destination::send(NET_DatagramSocket *_sock, const Message& _message) const {
    NET_SendDatagram(_sock, address, port, _message.getData(), _message.getLength());
}
