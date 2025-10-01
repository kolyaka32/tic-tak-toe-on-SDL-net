/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "destination.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "messages/confirmedMessage.hpp"
#include "messages/getPacket.hpp"


// Basic class for internet connection
class Reciepient {
 private:
    // System for confirmation of connection
    timer needResendApplyConnection = 0;            // Time, after which need resend apply connection message
    static const timer messageGetTimeout = 5000;    // Time after which connection is considered lost
    timer needDisconect = 0;                        // Time, after which connection will be recognized as disconected
    static const timer messageApplyTimeout = 2000;  // Time to send apply message to keep connecion
    // Array of messages, waiting for apply from connection, or resend if don't
    std::vector<Message*> unconfirmedMessages;
    // Array of indexes of last getted messages
    IndexesArray<10> getIndexes;
    //bool disconnected = false;

 public:
    Reciepient();
    ~Reciepient();
    // Address, where send to or recieve from
    Destination dest;
};


#endif  // (USE_SDL_NET)
