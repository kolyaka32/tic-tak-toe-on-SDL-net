/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "reciepient.hpp"

#if (USE_SDL_NET)


Reciepient::Reciepient(NET_Address* _address, Uint16 _port)
: dest(_address, _port) {}

Reciepient::~Reciepient() {}

void Reciepient::checkResending(NET_DatagramSocket *_sock) {
    for (int i=0; i < unconfirmedMessages.size(); ++i) {
        if (unconfirmedMessages[i].isNeedResend()) {
            dest.send(_sock, unconfirmedMessages[i]);
        }
    }
}

void Reciepient::checkNeedApplyConnection(NET_DatagramSocket* _sock) {
    if (getTime() > needResendApplyConnection) {
        sendConfirmed(_sock, ConfirmedMessage{ConnectionCode::ApplyConnection});
    }
}

void Reciepient::sendConfirmed(NET_DatagramSocket* _sock, const ConfirmedMessage& _message) {
    // Firstly sending it
    sendUnconfirmed(_sock, _message);
    // Adding to list to check status
    unconfirmedMessages.push_back(_message);
}

void Reciepient::sendUnconfirmed(NET_DatagramSocket* _sock, const Message& _message) {
    // Sending it
    dest.send(_sock, _message);
    // Updating send timer
    needResendApplyConnection = getTime() + messageApplyTimeout;
}

bool Reciepient::isAddress(const Destination& _dest) {
    return dest == _dest;
}

void Reciepient::applyMessage(Uint8 _index) {
    // Find that message
    for (int i=0; i < unconfirmedMessages.size(); ++i) {
        if (unconfirmedMessages[i].applyMessage(_index)) {
            // Delete it from list
            unconfirmedMessages.erase(unconfirmedMessages.begin() + i);
            break;
        }
    }
}

bool Reciepient::checkIndexUniqness(Uint8 _index) {
    return getIndexes.isUnique(_index);
}

#endif  // (USE_SDL_NET)
