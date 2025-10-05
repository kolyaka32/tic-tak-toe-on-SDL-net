/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdio>
#include "internet.hpp"

#if (USE_SDL_NET)


Internet::Internet()
: localhost(),  // Initialasing from getBroadcastAddress()
broadcast(getBroadcastAddress(), broadcastPort) {
    
}

Internet::~Internet() {}

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
            // Use this address
            snprintf(localhost, sizeof(localhost), "%s", address);
        }
    }
}

NET_Address* Internet::getBroadcastAddress() {
    // Update address of current machine
    getLocalAddress();

    // Get byte address of current machine (from IPv4)
    Uint8 values[4] {0};
    int i=0;
    for (const char* c = localhost; *c; ++c) {
        if (*c == '.') {
            i++;
            if (i == 4) {
                break;
            }
        } else {
            values[i] = values[i]*10 + *c - '0';
        }
    }
    char broadcastString[16];
    if (values[0] < 128) {
        // Mask: 255.0.0.0
        snprintf(broadcastString, sizeof(broadcastString), "%d.255.255.255", values[0]);
    } else if (values[0] < 192) {
        // Mask: 255.255.0.0
        snprintf(broadcastString, sizeof(broadcastString), "%d.%d.255.255", values[0], values[1]);
    } else if (values[0] < 224) {
        // Mask: 255.255.255.0
        snprintf(broadcastString, sizeof(broadcastString), "%d.%d.%d.255", values[0], values[1], values[2]);
    } else {
        snprintf(broadcastString, sizeof(broadcastString), "255.255.255.255");
    }
    return NET_ResolveHostname(broadcastString);
}


void Internet::openServer() {
    // Creating concrete socket at specified or random port
}

void Internet::openClient() {
    // Creating socket at random port
}

void Internet::close() {
    // Destrying getting socket
}

void Internet::disconnect() {
    // Sending message with quiting connection
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(gettingSocket, Message{Uint8(ConnectionCode::Quit)});
    }
    logAdditional("Disconnecting from games");
}


bool Internet::checkStatus() {
    return (getTime() > needDisconect);
}

void Internet::checkApplyMessages() {
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].checkNeedApplyConnection(gettingSocket);
    }
}

void Internet::checkResendMessages() {
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].checkResending(gettingSocket);
    }
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
        // Update wait timer
        needDisconect = getTime() + messageGetTimeout;

        if (source) {
            // Checking get message on special types
            switch ((ConnectionCode)datagram->buf[0]) {
            case ConnectionCode::Confirm:
                // Applying in sended array, that message was delivered
                source->applyMessage(datagram->buf[2]);
                break;

            case ConnectionCode::Null:
            case ConnectionCode::ApplyConnection:
                // Can be addtiotion to apply every connecrtion
                break;

            default:
                // Sending message, applying that message was get
                source->sendConfirmed(gettingSocket, ConfirmedMessage{ConnectionCode::Confirm, datagram->buf[1]});
                // Check, if already get it
                if (source->checkIndexUniqness(datagram->buf[1])) {
                    logAdditional("Get data with code: %u, index: %u", datagram->buf[0], datagram->buf[1]);
                    // In other cases - external updation
                    return datagram;
                }
            }
            return nullptr;
        } else {
            // Check on new connection
            if (datagram->buf[0] == (Uint8)ConnectionCode::Init && reciepients.size() < MAX_CONNECTIONS) {
                // Add new connection
                reciepients.push_back(Reciepient(datagram->addr, datagram->port));
            }
        }
    }
    return nullptr;
}

#endif  // (USE_SDL_NET)
