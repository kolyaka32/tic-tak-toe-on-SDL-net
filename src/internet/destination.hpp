/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "messages/confirmedMessage.hpp"


// Class with address and port for send operation
class Destination {
 protected:
    // Address and port, where can sending or recieve from
    #if (USE_WINSOCK)
    sockaddr_in address;
    #endif

 public:
    Destination(const sockaddr_in* address);
    Destination(const sockaddr* address, int size);
    Destination(const char* name, Uint16 port);

    // Operator for compare addresses (for search in list)
    bool operator==(const sockaddr_in* compareAddress) const;
    // Getters
    sockaddr* getAddress() const;
    const char* getName() const;
    Uint16 getPort() const;
};
