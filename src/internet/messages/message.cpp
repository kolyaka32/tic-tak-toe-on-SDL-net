/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "message.hpp"

#if (USE_SDL_NET)


Uint8 Message::globalMessageIndex = 1;

void Message::updateGlobalIndex() {
    // Upating global message index, skipping 0
    if (globalMessageIndex == 127) {
        globalMessageIndex = 1;
    } else {
        globalMessageIndex++;
    }
}

void Message::send(const Connection& _connection) {
    // Sending message itself
    _connection.send(packet);

    // Resetting timer
    nextResend = getTime() + MESSAGE_RESEND_TIMEOUT;
}

void Message::checkNeedResend(const Connection& _connection) {
    // Check, if get over timer
    if (getTime() > nextResend) {
        logAdditional("Resending packet with code: %u, index: %u", packet.getData()[0], messageIndex);
        send(_connection);
    }
}

bool Message::applyMessage(Uint8 _index) {
    return messageIndex == _index;
}

#endif  // (USE_SDL_NET)
