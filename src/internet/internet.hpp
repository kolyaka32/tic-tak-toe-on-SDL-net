/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "reciepient.hpp"


// Global class for send/recieve data from internet
class Internet {
 private:
    // Socket for recieve/send data (general)
    Socket socket;
    // Socket for broadcast recieve/send data
    Socket broadcastSocket;
    // Flag of disconnecting current user from main internet system
    bool disconnected;
    // Reciepients
    std::vector<Reciepient> reciepients;

 public:
    Internet();

    // Init part
    void connectTo(const Destination& dest);
    Uint16 getPort() const;
    const char* getHostName() const;
    void close();
    void disconnect();

    // Sending data to specialised user, without applience
    void sendFirst(const Destination& dest, const Message& message) const;
    // Sending data to all reciepients, without applience
    void sendAll(const Message& message);
    // Sending data to all reciepients, confirming for delievery
    void sendAllConfirmed(const ConfirmedMessage& message);

    // Control part
    void checkResendMessages();
    void checkNeedApplyConnection();
    bool checkStatus();  // Return true on disconect

    // Getting part
    const GetPacket* getNewMessages();
};

// Global system to send/recieve messages throw internet
extern Internet internet;
