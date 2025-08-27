/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "client.hpp"

#if (USE_SDL_NET)


Client::Client()
: Connection() {
    // Creating random recieving socket
    gettingSocket = NET_CreateDatagramSocket(nullptr, 0);

    #if (CHECK_CORRECTION)
    // Adding some packet loss for better testing
    NET_SimulateDatagramPacketLoss(gettingSocket, CONNECTION_LOST_PERCENT);
    #endif

    logAdditional("Client created, address: %s", getLocalIP());
}

Client::~Client() {
    logAdditional("Destroying client, closing net library");

    // Clearing rest data
    NET_DestroyDatagramSocket(gettingSocket);
    if (sendAddress) {
       NET_UnrefAddress(sendAddress);
    }

    // Closing new library
    NET_Quit();
}

void Client::tryConnect(const char* _address, Uint16 _port) {
    logAdditional("Trying connect to: address: %s, port: %u", _address, _port);

    sendAddress = NET_ResolveHostname(_address);
    sendPort = _port;

    // Check, if address is incorrect
    if (sendAddress == nullptr) {
        logAdditional("Can't find this address");
        return;
    }

    // Waiting, if get address
    NET_WaitUntilResolved(sendAddress, 20);

    // Check, if get address
    if (NET_GetAddressStatus(sendAddress) != 1) {
        logAdditional("Can't connect to this address");
        return;
    }

    logAdditional("Sending initialasing packet");
    // Sending some initialasing packet (for more chances)
    send(ConnectionCode::Init, 0);
    send(ConnectionCode::Init, 0);
    send(ConnectionCode::Init, 0);

    // Clearing temporary addresses
    NET_UnrefAddress(sendAddress);
    sendAddress = nullptr;
}

void Client::connectToLastMessage() {
    // Connecting to address from last message
    sendAddress = NET_RefAddress(recievedDatagram->addr);
    sendPort = recievedDatagram->port;
}

#endif  // (USE_SDL_NET)
