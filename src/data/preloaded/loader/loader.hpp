/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../logger.hpp"


// Load needed loader, depend on teting
#if ARCHIEVE_LOADING
#include "archieveLoader.hpp"
extern const ArchieveLoader dataLoader;
#else
#include "straightLoader.hpp"
extern const StraightLoader dataLoader;
#endif
