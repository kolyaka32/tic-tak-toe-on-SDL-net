/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "destination.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include <vector>
#include "messages/confirmedMessage.hpp"
#include "messages/getPacket.hpp"


// Basic class for internet connection
class Reciepient {
 private:
    // Address, where send to or recieve from
    Destination dest;
    // System for confirmation of connection
    timer needResendApplyConnection = 0;             // Time, after which need resend apply connection message
    static const timer messageApplyTimeout = 2000;   // Time to send apply message to keep connecion
    timer wasDisconected = 0;                        // Time, after which connection will be recognized as disconected
    static const timer connectionGetTimeout = 6000;  // Time, after which connection is considered lost
    // Array of messages, waiting for apply from connection, or resend if don't
    std::vector<ConfirmedMessage> unconfirmedMessages;
    // Array of indexes of last getted messages
    IndexesArray<10> getIndexes;

 public:
    Reciepient(NET_Address* address, Uint16 port);

    // Send part
    void sendConfirmed(NET_DatagramSocket* sock, const ConfirmedMessage& message);
    void sendUnconfirmed(NET_DatagramSocket* sock, const Message& message);

    // Check part
    void checkResending(NET_DatagramSocket* sock);
    bool checkDisconnect();
    void checkNeedApplyConnection(NET_DatagramSocket* sock);
    bool isAddress(const Destination& dest);
    void updateGetTimeout();
    void applyMessage(Uint8 index);
    bool checkIndexUniqness(Uint8 index);
    const char* getName() const;
};


#endif  // (USE_SDL_NET)
