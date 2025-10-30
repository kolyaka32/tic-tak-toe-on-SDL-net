/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "reciepient.hpp"

// Check, if need internet library
#if (USE_SDL_NET)


// Global class for send/recieve data from internet
class Internet {
 private:
    // Getting part
    NET_DatagramSocket* gettingSocket;
    // Flag of disconnecting current user from main internet system
    bool disconnected;

    // Special addresses
    char localhost[16];  // Address of current machine
    void getLocalAddress();

    // Reciepients
    std::vector<Reciepient> reciepients;

 public:
    Internet();

    // Init part
    Uint16 openServer();
    void openClient();
    void connectTo(NET_Address* address, Uint16 port);
    void close();
    void disconnect();
    const char* getLocalhost();

    // Sending data to specialised user, without applience
    template <typename ...Args>
    void sendFirst(Destination dest, ConnectionCode code, const Args ...args);
    // Sending data to all reciepients, without applience
    template <typename ...Args>
    void sendAll(ConnectionCode code, const Args ...args);
    // Sending data to all reciepients, confirming for delievery
    template <typename ...Args>
    void sendAllConfirmed(ConnectionCode code, const Args ...args);

    // Control part
    void checkResendMessages();
    void checkNeedApplyConnection();
    bool checkStatus();  // Return true on disconect

    // Getting part
    NET_Datagram* getNewMessages();
};

// Global system to send/recieve messages throw internet
extern Internet internet;


// Template function realisations
template <typename ...Args>
void Internet::sendFirst(Destination _dest, ConnectionCode _code, const Args ...args) {
    // Creating message
    Message message(Uint8(_code), args...);
    // Sending it here
    _dest.send(gettingSocket, message);
}

template <typename ...Args>
void Internet::sendAll(ConnectionCode _code, const Args ...args) {
    // Creating message
    Message message(Uint8(_code), args...);
    // Sending it to all
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(gettingSocket, message);
    }
}

template <typename ...Args>
void Internet::sendAllConfirmed(ConnectionCode _code, const Args ...args) {
    // Creating message
    ConfirmedMessage message(_code, args...);
    // Sending it to all reciepients
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendConfirmed(gettingSocket, message);
    }
}

#endif  // (USE_SDL_NET)
