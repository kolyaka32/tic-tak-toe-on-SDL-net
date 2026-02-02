/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "messages/getPacket.hpp"
#include "destination.hpp"


// Class for socket - object, from which send data and on which recieve it
// Also contains local address for it
class Socket {
 private:
    #if (USE_WINSOCK)
    sockaddr_in localAddress;     // Internet address to from
    SOCKET sck = INVALID_SOCKET;  // Socket itself
    Uint16 port;                  // Port at hich socket as created
    #endif  // (USE_WINSOCK)

    // Packet, with data that was recieved
    GetPacket packet;

 public:
    // Try open socket at specified port
    Socket(Uint16 port);
    // Open at random port
    Socket();
    ~Socket();
    Uint16 getPort() const;
    void send(const Destination& dest, const Message& message) const;
    GetPacket* recieve();
};
