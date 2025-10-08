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
    static const Uint16 broadcastPort = 8000;  // Port for broadcast send/recieve
    Destination broadcast;        // Address for sending data to whole network
    NET_Address* getBroadcastAddress();

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
    void sendFirst(const char* address, Uint16 port, ConnectionCode code, const Args ...args);
    // Sending data to all reciepients, without applience
    template <typename ...Args>
    void sendAll(ConnectionCode code, const Args ...args);
    // Sending data to all reciepients, confirming for delievery
    template <typename ...Args>
    void sendAllConfirmed(ConnectionCode code, const Args ...args);
    // Sending data to whole network
    template <typename ...Args>
    void sendBroadcast(ConnectionCode code, const Args ...args);

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
void Internet::sendFirst(const char* _address, Uint16 _port, ConnectionCode _code, const Args ...args) {
    // Creating send destination
    NET_Address* address = NET_ResolveHostname(_address);
    Destination dest(address, _port);
    // Creating message
    Message message(Uint8(_code), args...);
    // Waiting until hostname resolved
    if (NET_WaitUntilResolved(address, 10) == NET_SUCCESS) {
        // Sending it here
        dest.send(gettingSocket, message);
    }
    // Clearing address
    NET_UnrefAddress(address);
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

template <typename ...Args>
void Internet::sendBroadcast(ConnectionCode _code, const Args ...args) {
    broadcast.send(gettingSocket, Message(_code, args...));
}

#endif  // (USE_SDL_NET)
