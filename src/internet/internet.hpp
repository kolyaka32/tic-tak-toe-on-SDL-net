/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
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
    void sendFirst(Destination dest, const Message message);
    // Sending data to all reciepients, without applience
    void sendAll(const Message message);
    // Sending data to all reciepients, confirming for delievery
    void sendAllConfirmed(const ConfirmedMessage message);

    // Control part
    void checkResendMessages();
    void checkNeedApplyConnection();
    bool checkStatus();  // Return true on disconect

    // Getting part
    NET_Datagram* getNewMessages();
};

// Global system to send/recieve messages throw internet
extern Internet internet;

#endif  // (USE_SDL_NET)
