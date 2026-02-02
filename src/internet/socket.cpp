/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "socket.hpp"
#include "../data/time.hpp"


#if (USE_WINSOCK)
Socket::Socket(Uint16 _port) {
    // Create a SOCKET for listening for incoming connection requests.
    sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sck == INVALID_SOCKET) {
        printf("socket function failed with error: %ld\n", WSAGetLastError());
    }
    // Setting local address
    localAddress.sin_family = AF_INET;
    localAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    port = _port;
    localAddress.sin_port = htons(port);
    // Setting random seed from time
    SDL_srand(getTime());
    // Finding avaliable port
    // Setting socket to send from created local host (as back address)
    while (bind(sck, (SOCKADDR*)&localAddress, sizeof(localAddress)) == SOCKET_ERROR) {
        if (WSAGetLastError() == 10048) {
            // Trying find another port
            port = SDL_rand(10000);
            localAddress.sin_port = htons(port);
        } else {
            // Error
            logImportant("bind function failed with error %d\n", WSAGetLastError());
        }
    }
    // Setting socket to non-blocking mode
    DWORD nonBlocking = 1;
    if (ioctlsocket(sck, FIONBIO, &nonBlocking) != 0) {
        logImportant("Failed to set non-blocking");
    }

    // Setting socket to broadcast
    bool t = true;
    if (setsockopt(sck, SOL_SOCKET, SO_BROADCAST, (char*)&t, sizeof(true))) {
        logImportant("Can't set socket to broadcast");
    }

    logAdditional("Openned socket at port %d\n", ntohs(localAddress.sin_port));
}

Socket::~Socket() {
    if (closesocket(sck) == SOCKET_ERROR) {
        logImportant("closesocket function failed with error %d\n", WSAGetLastError());
    }
}

void Socket::send(const Destination& _dest, const Message& _message) const {
    if (sendto(sck, _message.getData(), _message.getLength(), 0, _dest.getAddress(), _dest.getSize()) < 0) {
        logImportant("Can't send data %d\n", WSAGetLastError());
    } else {
        logAdditional("Send sucsesfull: %d\n", _message.getLength());
    }
}
#endif  // (USE_WINSOCK)

Socket::Socket()
: Socket(SDL_rand(10000)) {}

Uint16 Socket::getPort() const {
    return port;
}

GetPacket* Socket::recieve() {
    return packet.tryGetData(sck);
}
