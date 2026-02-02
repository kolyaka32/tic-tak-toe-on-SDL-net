/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "messages/confirmedMessage.hpp"


// Class with address and port for send operation
class Destination {
 protected:
    // Adress and port, sending to
    #if (USE_WINSOCK)
    sockaddr_in address;
    #endif  // (USE_WINSOCK)

 public:
    Destination(const sockaddr_in* address);
    Destination(const sockaddr* address, int size);
    Destination(const char* name, Uint16 port);
    bool operator==(const sockaddr_in* compareAddress) const;
    const char* getName() const;
    Uint16 getPort() const;
    sockaddr* getAddress() const;
    int getSize() const;
};
