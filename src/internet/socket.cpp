/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "socket.hpp"



Socket::Socket() {
    // Create a SOCKET for listening for incoming connection requests.
    //sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sck = socket(AF_INET, SOCK_NONBLOCK, IPPROTO_UDP);
    #if (USE_WINSOCK)
    if (sck == INVALID_SOCKET) {
        logAdditional("Can't create socket with error: %ld", WSAGetLastError());
    }
    #endif
    #if (USE_SOCKET)
    if (sck == -1) {
        logAdditional("Can't create socket");
    }
    #endif
    // Setting local address
    localAddress.sin_family = AF_INET;
    localAddress.sin_addr.s_addr = INADDR_ANY;
}

Socket::~Socket() {
    #if (USE_WINSOCK)
    if (closesocket(sck) == SOCKET_ERROR) {
        logImportant("Closesocket function failed with error %d", WSAGetLastError());
    }
    #endif
    #if (USE_SOCKET)
    close(sck);
    #endif
}

int Socket::tryBind() {
    localAddress.sin_port = htons(port);
    return bind(sck, (sockaddr*)&localAddress, sizeof(localAddress));
}

void Socket::setNonBlockingMode() {
    // Setting socket to non-blocking mode
    #if (USE_WINSOCK)
    DWORD nonBlocking = 1;
    if (ioctlsocket(sck, FIONBIO, &nonBlocking) != 0) {
        logImportant("Can't set socket to non-blocking mode: %d", WSAGetLastError());
    }
    #endif
    /*#if (USE_SOCKET)
    #endif*/
}

void Socket::setReuseAddressMode() {
    // Setting socket to allow to reuse address
    bool t = true;
    if (setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, (char*)&t, sizeof(t))) {
        #if (USE_WINSOCK)
        logImportant("Can't set reusing socket: %d", WSAGetLastError());
        #else
        logImportant("Can't set reusing socket");
        #endif
    }
}

void Socket::setBroadcastMode() {
    // Setting socket to broadcast
    bool t = true;
    if (setsockopt(sck, SOL_SOCKET, SO_BROADCAST, (char*)&t, sizeof(t))) {
        #if (USE_WINSOCK)
        logImportant("Can't set socket to broadcast: %d", WSAGetLastError());
        #else
        logImportant("Can't set socket to broadcast");
        #endif
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
    int sendLength = sendto(sck, _message.getData(), _message.getLength(), 0, _dest.getAddress(), _dest.getSize());
    #if (CHECK_CORRECTION)
    if (sendLength < 0) {
        logImportant("Can't send data %d", WSAGetLastError());
    } else if (sendLength != _message.getLength()) {
        logAdditional("Don't send fully: %d", WSAGetLastError());
    } else {
        logAdditional("Send sucsesfull: %d", _message.getLength());
    }
    #endif
}

Uint16 Socket::getPort() const {
    return port;
}

GetPacket* Socket::recieve() {
    return packet.tryGetData(sck);
}
#if (USE_WINSOCK)
#endif  // (USE_WINSOCK)
