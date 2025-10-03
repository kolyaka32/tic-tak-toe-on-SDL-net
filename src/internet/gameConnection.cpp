/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameConnection.hpp"

#if (USE_SDL_NET)

#include "../data/cycleTemplate.hpp"
#include "../game/internet/connectionLostBox.hpp"
#include "../game/internet/terminatedBox.hpp"


GameConnection::GameConnection(const Connection& _connection)
: Connection(_connection) {
    // Resetting timers
    needResendApplyConnection = getTime();
    needDisconect = getTime() + MESSAGE_GET_TIMEOUT;
    logImportant("Created internet game connection, sending to: %s:%u", NET_GetAddressString(sendAddress), sendPort);
}

GameConnection::~GameConnection() {
    // Checking on game restart
    if (!CycleTemplate::isRestarted()) {
        logAdditional("Destroying game connection");
        // Sending message with quiting connection
        send(ConnectionCode::Quit, 0);

        // Clearing rest messages
        for (int i=0; i < unconfirmedMessages.size(); ++i) {
            delete unconfirmedMessages[i];
        }
    }
}

ConnectionCode GameConnection::updateMessages() {
    // Check, if disconnected
    if (disconnected) {
        checkReconnecting();
        return ConnectionCode::Null;
    } else {
        checkConnectionStatus();
        checkNeedApplyConnection();
        checkNeedResending();
        return checkNewMessage();
    }
}

void GameConnection::checkReconnecting() {
    // Checking, if restore connection
    switch (getCode()) {
    case ConnectionCode::Null:
        return;

    default:
        disconnected = false;
        ConnectionLostBox::reset();
        // Updating timer of last get message
        needDisconect = getTime() + MESSAGE_GET_TIMEOUT;
        // Sending new message that connection restored
        sendConfirmed(ConnectionCode::ApplyConnection);
        break;
    }
}

void GameConnection::checkConnectionStatus() {
    // Check, if getting over timer
    if (getTime() > needDisconect) {
        // Playing sounds with disconnect
        sounds.play(Sounds::Disconnect);
        // Disconneting, as lost connection
        logAdditional("Connection lost");
        // Showing disconect message
        ConnectionLostBox::activate();
        disconnected = true;
        return;
    }
}


ConnectionCode GameConnection::checkNewMessage() {
    // Checking, if get messages
    ConnectionCode code = getCode();
    if (code == ConnectionCode::Null) {
        return ConnectionCode::Null;
    }
    // Updating timer of last get message
    needDisconect = getTime() + MESSAGE_GET_TIMEOUT;

    // Writing getted data for debug
    logAdditional("Get packet with %u bytes, from %s, port: %u, code: %u, index: %u",
        recievedDatagram->buflen, NET_GetAddressString(recievedDatagram->addr),
        recievedDatagram->port, (Uint8)code, lastPacket->getData<Uint8>(1));

    // Getting index of message
    Uint8 index = lastPacket->getData<Uint8>();

    // Checking get message on type
    switch (code) {
    case ConnectionCode::Quit:
        // Connection forced terminatted
        // Playing sounds with disconnect
        sounds.play(Sounds::Disconnect);
        // Showing message of terminated connection
        TerminatedBox::activate();
        disconnected = true;
        logAdditional("Connection terminatted");
        return ConnectionCode::Null;

    case ConnectionCode::Confirm:
        // Applying in sended array, that message was delivered
        for (int i=0; i < unconfirmedMessages.size(); ++i) {
            if (unconfirmedMessages[i]->applyMessage(index)) {
                delete unconfirmedMessages[i];
                unconfirmedMessages.erase(unconfirmedMessages.begin() + i);
                break;
            }
        }
        return ConnectionCode::Null;

    case ConnectionCode::Init:
    case ConnectionCode::ApplyConnection:
        // Actioning like normal code
        code = ConnectionCode::Null;

    default:
        // Sending message, applying that message was get
        send(ConnectionCode::Confirm, index);
        // Updating timer
        needResendApplyConnection = getTime() + MESSAGE_APPLY_TIMEOUT;
        // Check, if need any additional actions with this code
        if (getIndexes.isUnique(index)) {
            // Adding to list for next checks
            getIndexes.add(index);
            #if (CHECK_CORRECTION)
            if (code != ConnectionCode::Null) {
                logAdditional("Get data with code: %u, index: %u", (Uint8)code, index);
            }
            #endif
            // In other cases - external updation
            return code;
        }
        return ConnectionCode::Null;
    }
}

void GameConnection::tryReconnect() {
    // Sending init message
    send(ConnectionCode::Init, 0);
    send(ConnectionCode::Init, 0);
}

#endif  // (USE_SDL_NET)
