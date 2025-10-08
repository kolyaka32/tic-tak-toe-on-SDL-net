/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "message.hpp"

#if (USE_SDL_NET)

#include "../../data/time.hpp"
#include "indexesArray.cpp"


// Message, waiting for applying of getting
class ConfirmedMessage : public Message {
 private:
    static Uint8 globalMessageIndex;
    static void updateGlobalIndex();
    Uint8 messageIndex;  // Index to check applying and getting messages
    static const Uint8 maxSendId = 128;  // Maximal number of send message ID
    timer nextResend;    // Time, when need to resend message
    static const timer messageResendTimeout = 250;  // Time after which need to resend message, as it was lost

 public:
    template <typename ...Args>
    ConfirmedMessage(ConnectionCode code, const Args ...args);
    bool isNeedResend();
    bool applyMessage(Uint8 index) const;  // Check, if that message arrived and need to clearing
};

template <typename ...Args>
ConfirmedMessage::ConfirmedMessage(ConnectionCode _code, const Args ...args)
: Message(Uint8(_code), globalMessageIndex, args...),
messageIndex(globalMessageIndex) {
    updateGlobalIndex();
}

#endif  // (USE_SDL_NET)
