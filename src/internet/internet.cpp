/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdio>
#include "internet.hpp"




Internet::Internet() {
    getLocalAddress();
    getBroadcastAddress();
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

void Internet::getBroadcastAddress() {
    char broadcastString[16];
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
    broadcastAddress = NET_ResolveHostname(broadcastString);
}

void Internet::send(Destination _dest, const Message& _message) const {
    NET_SendDatagram(gettingSocket, _dest.getAddress(), _dest.getPort(), _message.getData(), _message.getLength());
}
