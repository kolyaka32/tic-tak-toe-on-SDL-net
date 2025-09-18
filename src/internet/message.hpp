/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "../data/time.hpp"


// Message, waiting for applying of getting
class Message {
 private:
    static Uint8 globalMessageIndex;
    static void updateGlobalIndex();
    Uint8 messageIndex;  // Index to check applying and getting messages
    timer nextResend;    // Time, when need to resend message
    SendPacket packet;   // Packet itself

 protected:
    void resend(const Connection& connection);

 public:
    template <typename ...Args>
    Message(const Connection& connection, ConnectionCode code, Args&& ...args);
    void checkNeedResend(const Connection& connection);
    bool applyMessage(Uint8 index);  // Check, if that message arrived and need to clearing
};

template <typename ...Args>
Message::Message(const Connection& _connection, ConnectionCode _code, Args&& ...args)
: messageIndex(globalMessageIndex),
packet(Uint8(_code), messageIndex, args...) {
    logAdditional("Firstly sending message with code: %u, index: %u", (Uint8)_code, messageIndex);
    // Firstly sending message
    resend(_connection);
    updateGlobalIndex();
}

#endif  // (USE_SDL_NET)
