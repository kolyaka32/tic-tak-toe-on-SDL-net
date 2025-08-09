/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Load needed loader, depend on teting
#if ARCHIEVE_LOADING
#include "archieveLoader.hpp"
#else
#include "straightLoader.hpp"
#endif


// Selecting loader for data, depend on testing
#if ARCHIEVE_LOADING
extern const ArchieveLoader dataLoader;
#else
extern const StraightLoader dataLoader;
#endif
