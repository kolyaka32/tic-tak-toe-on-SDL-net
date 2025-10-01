/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "messages/confirmedMessage.hpp"
#include "messages/getPacket.hpp"
#include "../data/logger.hpp"


// Basic class for internet connection
class Connection {
 protected:
    

 public:
    Connection();
    Connection(const Connection& connection);
    ~Connection();
    // Function for recieve new packets and update packets
    ConnectionCode getCode();
    // Packet with last getted data
    GetPacket* lastPacket = nullptr;

    // Function for get local IP address in IPv4 format
    static const char* getLocalIP();
};

#endif  // (USE_SDL_NET)
