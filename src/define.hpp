/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "testing.hpp"


// Global flags of compilation
// External libraries linkage
#define USE_SDL_IMAGE        true   // Library for load external images from disk
#define USE_SDL_MIXER        true   // Library for play sounds/music
#define USE_SDL_FONT         true   // Library for draw text at screen
#define USE_SDL_NET          true   // Library for internet connection by UDP/TCP
#define USE_LIBZIP           true   // Library for compress data to zip archives
// Use setting file for store data between seccions  
#define USE_SETTING_FILE     true
// Preloaded GFX (could be created runtime)
#define PRELOAD_TEXTURES     true   // Preload textures
#define PRELOAD_ANIMATIONS   false  // Preload GIF animaions
#define PRELOAD_FONTS        true   // Preload fonts
#define PRELOAD_SOUNDS       true   // Preload sounds
#define PRELOAD_MUSIC        true   // Preload music
// Use archive for store additional GFX
#define PRELOAD_DATA PRELOAD_TEXTURES | PRELOAD_FONTS | PRELOAD_ANIMATIONS | PRELOAD_SOUNDS | PRELOAD_MUSIC


// System numbers
#define WINDOW_NAME "Tic-tac-toe on SDL"   // System game name

// Base file names
// File with all GFX
#if (PRELOAD_DATA)
#define DATA_FILE "data-tic-tac-toe.dat"
#endif

// File with all saved data (language, settings, volumes...)
#if USE_SETTING_FILE
#define SETTING_FILE "settings-tic-tac-toe.ini"
#endif

// Number of active connections in internet part
#if USE_SDL_NET
#define MAX_CONNECTIONS 1
#endif
