/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// System numbers
#define WINDOW_NAME "Tic-tac-toe on SDL"  // System game name
#define CELL_SIDE 100                     // Width and height of mine in pixels
#define SEPARATOR 5                       // Width of separator between cells in pixels

// Internet constants
#define BASE_PORT 8000                      // Base port to create/connect
#define MAX_SEND_ID 128                     // Maximal number of send message ID
#define MESSAGE_GET_TIMEOUT 5000            // Time after which connection is considered lost
#define MESSAGE_APPLY_TIMEOUT 2000          // Time to send apply message to keep connecion
#define MESSAGE_RESEND_TIMEOUT 250          // Time after which need to resend message, as it was lost
#define CONNECTION_LOST_PERCENT 0           // Option for better testing of connection stability

// Base file names
#define SETTING_FILE "settings-tic-tac-toe.ini"  // File with all starting data (width, height...)
#define DATA_FILE "data-tic-tac-toe.dat"         // File with all GFX
