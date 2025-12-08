/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdio>
#include "internet.hpp"

#if (USE_SDL_NET)


Internet::Internet() {
    getLocalAddress();
    logAdditional("Internet created correctly");
}

void Internet::getLocalAddress() {
    // Getting local addresses
    int addressesNumber = 0;
    NET_Address** addresses = NET_GetLocalAddresses(&addressesNumber);

    // Finding usedull address
    for (int i=0; i < addressesNumber; ++i) {
        const char* address = NET_GetAddressString(addresses[i]);
        bool usefull = true;
        // Check, if not IPv6 address
        for (const char* c = address; *c; ++c) {
            if (*c == ':') {
                usefull = false;
                break;
            }
        }
        // Check, if not basic '127.0.0.1'
        if (usefull && strcmp(address, "127.0.0.1")) {
            // Writing get address to buffer
            snprintf(localhost, sizeof(localhost), "%s", address);
            // Clear used addresses
            NET_FreeLocalAddresses(addresses);
            return;
        }
    }
    NET_FreeLocalAddresses(addresses);
}

Uint16 Internet::openServer() {
    // Creating concrete socket at specified or random port, if busy
    // Setting basic create port
    Uint16 currentPort = basePort;
    gettingSocket = NET_CreateDatagramSocket(nullptr, currentPort);

    // Finding avalialble port
    SDL_srand(0);
    while (gettingSocket == nullptr) {
        // Creating random port
        currentPort = SDL_rand(10000);
        // Getting new socket
        gettingSocket = NET_CreateDatagramSocket(nullptr, currentPort);
    };
    logAdditional("Server created, address: %s, port: %u", localhost, currentPort);

    #if (CHECK_CORRECTION)
    // Adding some packet loss for better testing
    NET_SimulateDatagramPacketLoss(gettingSocket, CONNECTION_LOST_PERCENT);
    #endif

    return currentPort;
}

void Internet::openClient() {
    // Creating socket at random port
    gettingSocket = NET_CreateDatagramSocket(nullptr, 0);
    logAdditional("Client created, address: %s", localhost);
}

void Internet::connectTo(NET_Address* _address, Uint16 _port) {
    // Add new connection
    reciepients.push_back(Reciepient(_address, _port));
    logAdditional("Connecting to %s:%u", _address, _port);
}

void Internet::close() {
    logAdditional("Close datagramm socket");
    // Closing all reciepients
    reciepients.clear();
    // Destrying main getting socket
    NET_DestroyDatagramSocket(gettingSocket);
}

void Internet::disconnect() {
    // Sending message with quiting connection
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(gettingSocket, Message{Uint8(ConnectionCode::Quit), 1});
    }
    logAdditional("Disconnecting from games");
}

const char* Internet::getLocalhost() {
    return localhost;
}

void Internet::checkResendMessages() {
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].checkResending(gettingSocket);
    }
}

void Internet::checkNeedApplyConnection() {
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].checkNeedApplyConnection(gettingSocket);
    }
}

bool Internet::checkStatus() {
    // Resetting flag
    disconnected = true;
    // Check all connections
    for (int i=0; i < reciepients.size(); ++i) {
        disconnected &= reciepients[i].checkDisconnect();
    }
    return disconnected;
}

NET_Datagram* Internet::getNewMessages() {
    // Get message
    NET_Datagram *datagram = nullptr;
    if (NET_ReceiveDatagram(gettingSocket, &datagram) && datagram && datagram->buflen > 1) {
        // Get message source
        Reciepient* source = nullptr;
        for (int i=0; i < reciepients.size(); ++i) {
            if (reciepients[i].isAddress(Destination(datagram->addr, datagram->port))) {
                source = &reciepients[i];
                break;
            }
        }

        if (source) {
            // Logging get message
            #if (CHECK_ALL)
            char buffer[100];
            for (int i=0; i < datagram->buflen; ++i) {
                buffer[i] = char(datagram->buf[i] + '0');
            }
            buffer[datagram->buflen] = '\0';
            logAdditional("Get message from %s, size %u: %s", source->getName(), datagram->buflen, buffer);
            #endif

            // Update wait timer
            source->updateGetTimeout();

            // Checking get message on special types
            switch ((ConnectionCode)datagram->buf[0]) {
            case ConnectionCode::Confirm:
                // Applying in sended array, that message was delivered
                source->applyMessage(datagram->buf[1]);
                break;

            case ConnectionCode::Null:
            case ConnectionCode::ApplyConnection:
                // Can be addtiotion to apply every connection

                // Sending message, applying that message was get
                source->sendUnconfirmed(gettingSocket, Message{Uint8(ConnectionCode::Confirm), datagram->buf[1]});
                break;

            default:
                // Sending message, applying that message was get
                source->sendUnconfirmed(gettingSocket, Message{Uint8(ConnectionCode::Confirm), datagram->buf[1]});

                // Check, if already get it
                if (source->checkIndexUniqness(datagram->buf[1])) {
                    logAdditional("Get data with code: %u, index: %u", datagram->buf[0], datagram->buf[1]);
                    // In other cases - external updation
                    return datagram;
                }
            }
            return nullptr;
        } else {
            // Logging get message
            logAdditional("Get unknown message, type %u, size %u", datagram->buf[0], datagram->buflen);
            // Special action, if address is unknown
            return datagram;
        }
    }
    return nullptr;
}

void Internet::sendFirst(Destination _dest, const Message _message) {
    // Sending it here
    _dest.send(gettingSocket, _message);
}

void Internet::sendAll(const Message _message) {
    // Sending it to all
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(gettingSocket, _message);
    }
}

void Internet::sendAllConfirmed(const ConfirmedMessage _message) {
    // Sending it to all reciepients
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendConfirmed(gettingSocket, _message);
    }
}

#endif  // (USE_SDL_NET)
