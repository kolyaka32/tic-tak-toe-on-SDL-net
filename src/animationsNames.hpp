/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_ANIMATIONS)

// Names of gif animation
enum class Animations : unsigned {

    // Count of all animations
    Count,
};

// File names of the corresponding animations
extern const char* animationsFilesNames[unsigned(Animations::Count)];

#endif  // (PRELOAD_ANIMATIONS)
