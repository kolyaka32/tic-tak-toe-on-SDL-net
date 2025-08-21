/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "loader.hpp"


// Selecting loader for data, depend on testing
#if ARCHIEVE_LOADING
const ArchieveLoader dataLoader{};
#else
const StraightLoader dataLoader{};
#endif
