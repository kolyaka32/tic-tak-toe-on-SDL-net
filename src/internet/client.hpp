/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"

// Check, if need internet library
#if (USE_SDL_NET)


// Class with starting part of internet connection, that trying to connect to address
class Client : public Connection {
 public:
    Client();
    ~Client();
    void tryConnect(const char* address, Uint16 port);
    void connectToLastMessage();

    // Static objects for save inputted parameters
    static char baseIP[15];
    static char basePort[6];
};

#endif  // (USE_SDL_NET)
