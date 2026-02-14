/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_platform_defines.h>
#include "../internetCodes.hpp"
#include "../data/logger.hpp"
#include "../data/array.hpp"


// Select library depend on platform
// Windows
#if ((USE_NET) && (SDL_PLATFORM_WINDOWS))
#define USE_WINSOCK true   // Internet library for windows (winsock2.h)
#define NET_SELECTED true
// Including library itself
#include <winsock2.h>
// Including library for getting localhost
#include <iphlpapi.h>
#endif  // ((USE_NET) && (SDL_PLATFORM_WINDOWS))

// Unix
#if ((USE_NET) && (SDL_PLATFORM_UNIX))
#define USE_SOCKET true  // Internet library for unix
#define NET_SELECTED true
// Including librry itself
#include 
#endif  // ((USE_NET) && (SDL_PLATFORM_UNIX))


// Check on define correction
#if ((USE_NET) && (NET_SELECTED != true))
#error "Can't find internet library"
#else  // (!USE_NET)

// Net initialisation function
bool initNet();
// Net closing function
void closeNet();
// Get local host name for sharing
char* getLocalHostName();


// Functions for write data for send in correct byte order
Uint8  writeNet(Uint8 object);
Sint8  writeNet(Sint8 object);
char   writeNet(char object);
Uint8  writeNet(ConnectionCode object);
Uint16 writeNet(Uint16 object);
Sint16 writeNet(Sint16 object);
Uint32 writeNet(Uint32 object);
Sint32 writeNet(Sint32 object);
float  writeNet(float object);
Uint64 writeNet(Uint64 object);
Sint64 writeNet(Sint64 object);

// Functions for read data from getted internet message
Uint8  readNet(Uint8 object);
Sint8  readNet(Sint8 object);
char   readNet(char object);
ConnectionCode readNet(ConnectionCode object);
Uint16 readNet(Uint16 object);
Sint16 readNet(Sint16 object);
Uint32 readNet(Uint32 object);
Sint32 readNet(Sint32 object);
float  readNet(float object);
Uint64 readNet(Uint64 object);
Sint64 readNet(Sint64 object);

#endif  // (!USE_NET)
