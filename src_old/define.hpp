/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

// Debuging modifiers
#define DEBUG true
#define CHECK_CORRECTION DEBUG
#define ARCHIEVE_LOADING !DEBUG
#define SCROLLER_SOUND SND_count
#define CONNECTION_LOST_PERCENT 20

// System numbers
#define WINDOWNAME "Tic-tac-toe on SDL"  // System game name
#define CELL_SIDE 64                     // Width and height of mine in pixels
#define SEPARATOR 4                      // Width of separator between cells

// Internet constants
#define BASE_PORT 2000                   // Base port to create/connect
#define INTERNET_BUFFER 3                // Size of data to send/recieve by connecion
//#define INTERNET_BUFFER 5                   // Size of data to send/recieve by connecion (new)
#define MAX_SEND_ID 128                     // Maximal number of send message ID
#define MESSAGE_GET_TIMEOUT 2000         // Time after which connection is considered lost
#define MESSAGE_NULL_TIMEOUT 800         // Time to send NULL message to keep connecion
#define MESSAGE_APPLY_TIMEOUT 600        // Time to apply arriving message

// Base file names
#define SETTING_FILE "settings4.ini"     // File with all starting data (width, height...)
#define DATA_FILE "data4.dat"            // File with all pictures, music...

// Base game colors
// Global game colors
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}
#define GREY {175, 175, 175, 255}
#define BACKGROUND_COLOR 0, 0, 0, 255

// Macroses
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define SET_MIN(value, min) (value = value < min ? min : value)
#define SET_MAX(value, max) (value = value > max ? max : value)
#define sqr(value) ((value) * (value))
