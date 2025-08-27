/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"

// Check, if need internet library
#if (USE_SDL_NET)


// Class for create server and wait to connect from another side
class Server : public Connection {
 private:
    Uint16 currentPort;
    static const Uint16 basePort = 8000;

 public:
    Server();
    ~Server();
    Uint16 getPort();
    void connectToLastMessage();
};

#endif  // (USE_SDL_NET)
