/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../data/array.hpp"

// Check, if need internet library
#if (USE_SDL_NET)

#include "../../internetCodes.hpp"
#include <SDL3_net/SDL_net.h>


// Function for correct bits order to prevent wrong understanding
template <typename T>
T swapLE(T object);

#endif  // (USE_SDL_NET)
