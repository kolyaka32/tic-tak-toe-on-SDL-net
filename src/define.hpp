#pragma once

// Extra modifications for game
#define DEBUG false
#define ARCHIEVE_LOADING true
#define SCROLLER_SOUND SND_count

// System numbers
#define WINDOWNAME "Tic-tac-toe on SDL"  // System game name
#define CELL_SIDE 64                     // Width and height of mine in pixels
#define SEPARATOR 4                      // Width of separator between cells
#define GAME_WIDTH (CELL_SIDE + SEPARATOR) * fieldWidth  // Width of game area
#define GAME_HEIGHT GAME_WIDTH           // Height of game area
#define SCREEN_WIDTH (GAME_WIDTH)        // Width of all screen
#define SCREEN_HEIGHT (GAME_HEIGHT)      // Height of all screen

// Internet numbers
#define BASE_PORT 2000                   // Base port to create/connect
#define INTERNET_BUFFER 3                // Size of data to send/recieve by connecion
#define MESSAGE_TIMEOUT 5000             // Time after which connection is considered lost
#define MESSAGE_NULL 2000                // Time to send NULL message to keep connecion

// Base file names
#define SETTING_FILE "settings4.ini"     // File with all starting data (width, height...)
#define DATA_FILE "data4.dat"            // File with all pictures, music...

// Base game colors
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define GREY {32, 32, 32, 255}
#define BACKGROUND_COLOR 0, 0, 0, 255

// Types of data
typedef uint8_t coord;      // Type of data for coordinates
typedef uint16_t count;     // Type of data for mines counters

// Types of language
enum LNG_types{
    LNG_ENGLISH,  // English language
    LNG_RUSSIAN   // Russian language
};

#define LNG_count 2  // Final counter of all languages

// Macroses
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)