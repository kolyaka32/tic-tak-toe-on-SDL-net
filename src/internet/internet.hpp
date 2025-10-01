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

    // Special addresses
    char localhost[16];  // Address of current machine
    void getLocalAddress();
    NET_Address* broadcastAddress = nullptr;  // Address for sending data to whole network
    void getBroadcastAddress();

    // Reciepients
    std::vector<Reciepient> reciepients;

 protected:
    void send(Destination dest, const Message& message) const;

 public:
    Internet();
    ~Internet();

    // Sending data to all reciepients, without applience
    template <typename ...Args>
    void sendAll(ConnectionCode code, const Args ...args);
    // Sending data to all reciepients, confirming for delievery
    template <typename ...Args>
    void sendAllConfirmed(ConnectionCode code, const Args ...args);
    // Sending data to whole network
    template <typename ...Args>
    void sendBroadcast(Uint16 port, ConnectionCode code, const Args ...args);
};

extern Internet internet;


// Template function realisations
template <typename ...Args>
void Internet::sendAll(ConnectionCode _code, const Args ...args) {
    // Creating message
    Message mess();
    // Sending it to all
    for (int i=0; i < reciepients.size(); ++i) {
        send(reciepients[i], mess);
    }
}

template <typename ...Args>
void Internet::sendAllConfirmed(ConnectionCode _code, const Args ...args) {
    // Adding new message to confirme array and send it
    /*Message* newMessage = new Message{*this, _code, args...};
    unconfirmedMessages.push_back(newMessage);
    // Updating timer
    needResendApplyConnection = getTime() + MESSAGE_APPLY_TIMEOUT;*/
    for (int i=0; i < reciepients.size(); ++i) {
        // Adding to apply list
        ConfirmedMessage* d = new ConfirmedMessage(_code, args...);
        //unconfirmedMessages.push_back(newMessage);
        // Sending it firstly
        send(reciepients[i], d);
    }
}

template <typename ...Args>
void Internet::sendBroadcast(Uint16 _port, ConnectionCode _code, const Args ...args) {
    send(Destination(broadcastAddress, _port), Message(_code, args));
}

#endif  // (USE_SDL_NET)
