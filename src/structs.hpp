// Base in-game global structs
#pragma once

#include "include.hpp"
#include "dataLoader.hpp"
#include "entity.hpp"

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

// Data for creating fonts
#if FNT_count
extern Uint8* fontMemory;  // Memory with font data
extern uint64_t fontSize;  // Size of memory buffer
#endif

// Creating main varables
extern App app;  // Global main render and window

// All textures
#if IMG_count
extern SDL_Texture* Textures[IMG_count];  // Array of all textures
#endif

// All animations
#if ANI_count
extern IMG_Animation* Animations[ANI_count];  // Array of all animations
#endif

// All music trcks
#if MUS_count
extern Mix_Music* Musics[MUS_count];      // Array of all music
#if ARCHIEVE_LOADING
extern SDL_RWops* MusicsData[MUS_count];  // Array of data for music
#endif
#endif

// All effects sounds
#if SND_count
extern Mix_Chunk* Sounds[SND_count];  // Array of all sound effects
#endif

// Flags of running
extern bool running;  // Flag of main cycle work
extern bool loosing;  // Flag of showing loosing screen
extern bool winning;  // Flag of showing winning screen
extern bool nobody;   // Flag of showing screen with nobody win
extern bool restart;  // Flag of restarting game with other parametrs

// Game parametrs
extern Uint8 fieldWidth;    // Width and height of field
extern Uint8 winWidth;      // Width, which need for win
extern Uint8 queue;         // Queue of current player
extern Uint8 player;        // Number of player, which selected
extern std::string baseIP;  // Saved ip for better expirience
extern std::string basePort;  // Saved connection port for better expirience