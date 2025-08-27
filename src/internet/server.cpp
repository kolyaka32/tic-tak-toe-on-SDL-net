/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "server.hpp"

// Check, if need internet library
#if (USE_SDL_NET)


Server::Server()
: Connection() {
    // Resetting basic connecting port
    currentPort = basePort;

    // Finding avalialble port
    SDL_srand(0);
    while ((gettingSocket = NET_CreateDatagramSocket(nullptr, currentPort)) == nullptr) {
        // Creating another random port
        currentPort = SDL_rand(10000);
    }

    #if (CHECK_CORRECTION)
    // Adding some packet loss for better testing
    NET_SimulateDatagramPacketLoss(gettingSocket, CONNECTION_LOST_PERCENT);
    #endif
    logAdditional("Server created, address: %s, port: %u", getLocalIP(), currentPort);
}

Server::~Server() {
    logAdditional("Destroying server, closing net library");

    // Clearing rest data
    NET_DestroyDatagramSocket(gettingSocket);
    if (sendAddress) {
       NET_UnrefAddress(sendAddress);
    }

    // Closing new library
    NET_Quit();
}

Uint16 Server::getPort() {
    return currentPort;
}

void Server::connectToLastMessage() {
    // Can be additional checks on versions
    // Connecting to address from last message
    sendAddress = NET_RefAddress(recievedDatagram->addr);
    sendPort = recievedDatagram->port;
}

#endif  // (USE_SDL_NET)
