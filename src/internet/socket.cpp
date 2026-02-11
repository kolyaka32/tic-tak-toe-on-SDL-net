/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "socket.hpp"


#if (USE_WINSOCK)
Socket::Socket() {
    // Create a SOCKET for listening for incoming connection requests.
    sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sck == INVALID_SOCKET) {
        printf("socket function failed with error: %ld", WSAGetLastError());
    }
    // Setting local address
    localAddress.sin_family = AF_INET;
    localAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
}

Socket::~Socket() {
    if (closesocket(sck) == SOCKET_ERROR) {
        logImportant("Closesocket function failed with error %d", WSAGetLastError());
    }
}

int Socket::tryBind() {
    localAddress.sin_port = htons(port);
    return bind(sck, (SOCKADDR*)&localAddress, sizeof(localAddress));
}

void Socket::setNonBlockingMode() {
    // Setting socket to non-blocking mode
    DWORD nonBlocking = 1;
    if (ioctlsocket(sck, FIONBIO, &nonBlocking) != 0) {
        logImportant("Can't set socket to non-blocking mode");
    }
}

void Socket::setReuseAddressMode() {
    // Setting socket to allow to reuse address
    bool t = true;
    if (setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, (char*)&t, sizeof(t))) {
        logImportant("Can't set reusing socket");
    }
}

void Socket::setBroadcastMode() {
    // Setting socket to broadcast
    bool t = true;
    if (setsockopt(sck, SOL_SOCKET, SO_BROADCAST, (char*)&t, sizeof(t))) {
        logImportant("Can't set socket to broadcast");
    }
}

void Socket::tryBindTo(Uint16 _port) {
    // Setting basic port
    port = _port;
    // Setting random seed from time
    SDL_srand(0);
    // Finding avaliable port
    // Setting socket to send from created local host (as back address)
    while (tryBind() == SOCKET_ERROR) {
        // Check, if port already using
        if (WSAGetLastError() == WSAEADDRINUSE) {
            // Finding another port
            port = SDL_rand(40000) + 1500;
        } else {
            // Error
            logImportant("bind function failed with error %d", WSAGetLastError());
        }
    }
    setNonBlockingMode();
    logAdditional("Openned socket at port %d", port);
}

void Socket::tryBindTo() {
    // Setting random seed from time
    SDL_srand(0);
    tryBindTo(SDL_rand(40000) + 1500);
}

void Socket::setRecieveBroadcast() {
    // Set, that any app could use that port (for many apps run simultaneously)
    setReuseAddressMode();
    // Setting basic port for broadcast
    port = BROADCAST_PORT;
    // Tring to set this port to use
    if (tryBind() == SOCKET_ERROR) {
        logImportant("Brodcast bind function failed with error %d", WSAGetLastError());
    }
    setNonBlockingMode();
    logAdditional("Openned broadcast socket at port %d", port);
}

void Socket::setSendBroadcast() {
    // Setting random seed from time
    SDL_srand(0);
    // Setting at random port
    tryBindTo(SDL_rand(40000) + 1500);
    // Setting to allow send broadcast messages
    setBroadcastMode();
}

void Socket::send(const Destination& _dest, const Message& _message) const {
    if (sendto(sck, _message.getData(), _message.getLength(), 0, _dest.getAddress(), _dest.getSize()) < 0) {
        logImportant("Can't send data %d", WSAGetLastError());
    } else {
        logAdditional("Send sucsesfull: %d", _message.getLength());
    }
}

Uint16 Socket::getPort() const {
    return port;
}

GetPacket* Socket::recieve() {
    return packet.tryGetData(sck);
}

#endif  // (USE_WINSOCK)
