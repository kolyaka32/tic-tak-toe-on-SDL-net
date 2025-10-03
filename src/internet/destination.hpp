/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "messages/message.hpp"


// Class with address and port for send operation
class Destination {
 private:
    // Adress and port of client, sending to
    NET_Address* address;
    Uint16 port;

 public:
    Destination(NET_Address* address, Uint16 port);
    ~Destination();
    bool operator==(const Destination& b);
    void send(NET_DatagramSocket* sock, const Message& message) const;
};

#endif  // (USE_SDL_NET)
