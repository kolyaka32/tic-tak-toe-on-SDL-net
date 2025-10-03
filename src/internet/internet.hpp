/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "messages/confirmedMessage.hpp"
#include "reciepient.hpp"

// Check, if need internet library
#if (USE_SDL_NET)


// Global class for send/recieve data from internet
class Internet {
 private:
    // Getting part
    NET_DatagramSocket* gettingSocket;
    NET_Datagram* recievedDatagram;
    // Check timer
    static const timer messageGetTimeout = 5000;  // Time after which connection is considered lost
    timer needDisconect = 0;                      // Time, after which connection will be recognized as disconected
    // Array of indexes of last getted messages
    IndexesArray<10> getIndexes;
    //bool disconnected = false;

    // Special addresses
    char localhost[16];  // Address of current machine
    void getLocalAddress();
    static const Uint16 broadcastPort = 8000;  // Port for broadcast send/recieve
    Destination broadcast;        // Address for sending data to whole network
    NET_Address* getBroadcastAddress();

    // Reciepients
    std::vector<Reciepient> reciepients;

 protected:
    //

 public:
    Internet();
    ~Internet();

    // Init part
    void openServer();
    void openClient();
    void close();
    void disconnect();

    // Connectinf part
    void connectTo();  // ! arguments

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
    bool checkStatus();  // Return true on disconect
    void checkApplyMessages();
    void checkResendMessages();

    // Getting part
    GetPacket getNewMessages();  // ! way it work
};

extern Internet internet;


// Template function realisations
template <typename ...Args>
void Internet::sendAll(ConnectionCode _code, const Args ...args) {
    // Creating message
    Message message(_code, args...);
    // Sending it to all
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(message);
    }
}

template <typename ...Args>
void Internet::sendAllConfirmed(ConnectionCode _code, const Args ...args) {
    // Creating message
    ConfirmedMessage message(_code, args...);
    for (int i=0; i < reciepients.size(); ++i) {
        // Sending it
        reciepients[i].sendConfirmed(gettingSocket, message);
    }
}

template <typename ...Args>
void Internet::sendBroadcast(ConnectionCode _code, const Args ...args) {
    broadcast.send(gettingSocket, Message(_code, args));
}

#endif  // (USE_SDL_NET)
