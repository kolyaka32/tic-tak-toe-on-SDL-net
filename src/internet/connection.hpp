/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "data.hpp"
#include "../data/logger.hpp"


// Internet constants
#define MAX_SEND_ID 128                     // Maximal number of send message ID
#define MESSAGE_GET_TIMEOUT 5000            // Time after which connection is considered lost
#define MESSAGE_APPLY_TIMEOUT 2000          // Time to send apply message to keep connecion
#define MESSAGE_RESEND_TIMEOUT 250          // Time after which need to resend message, as it was lost


// Basic class for internet connection
class Connection {
 protected:
    // Getting part
    NET_DatagramSocket* gettingSocket;
    NET_Datagram* recievedDatagram;

    // Sending part
    NET_Address* sendAddress;
    Uint16 sendPort;

 public:
    Connection();
    Connection(const Connection& connection);
    ~Connection();
    // Templated function for send any order of data
    template <typename ...Args>
    void send(ConnectionCode code, Uint8 index, Args ...args);
    void send(const SendPacket& _packet) const;
    // Function for recieve new packets and update packets
    ConnectionCode getCode();
    // Packet with last getted data
    GetPacket* lastPacket = nullptr;

    // Function for get local IP address in IPv4 format
    static const char* getLocalIP();
};


template <typename ...Args>
void Connection::send(ConnectionCode _code, Uint8 index, Args ...args) {
    #if (CHECK_CORRECTION)
    if (sendAddress == nullptr || sendPort == 0) {
        logAdditional("Can't send packet at unspecified address");
        return;
    }
    #endif
    // Creating new send packet
    SendPacket packet(Uint8(_code), index, args...);
    // Sending it
    const void* d = packet.getData();
    int s = packet.getLength();
    NET_SendDatagram(gettingSocket, sendAddress, sendPort, d, s);
    // Destroying packet
}

#endif  // (USE_SDL_NET)
