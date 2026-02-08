/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "soundsNames.hpp"

#if (PRELOAD_SOUNDS)


// File names of the corresponding sounds
const char* soundsFilesNames[unsigned(Sounds::Count)] = {
    // Game part
    "snd/turn.wav",
    "snd/reset.wav",
    "snd/win.wav",
    "snd/loose.wav",

    // Internet connection part
    "snd/disconnect.wav",

    // Screamer
    "snd/laugh.wav",
};

#endif  // (PRELOAD_SOUNDS)
