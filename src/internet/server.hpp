/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"


// Class for create server and wait to connect from another side
class Server : public Connection {
 private:
    Uint16 currentPort;

 public:
    Server();
    ~Server();
    Uint16 getPort();
    void connectToLastMessage();
};
