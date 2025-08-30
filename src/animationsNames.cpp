/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "animationsNames.hpp"


// Check, if can load animations and should preload it
#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)


// File names of the corresponding textures
const char* animationsFilesNames[unsigned(Animations::Count)] = {

};

#endif  // (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
