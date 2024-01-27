#pragma once

#include "baseGUI.hpp"
#include "structs.hpp"

// Working with text
// Functions for setting text at his place and his text
void setAllText();  
// Function of updating translation of all texts
void updateTranslation(LNG_types language);
// Function of clearing text SELCTED_BOX_types
void clearAllText();

// Pause menu with settings
void pause();

// First loaded menu, where player can choose mode, choose settings
void selectMenu();

// Types of numerated static texts
enum TXT_types{
    TXT_SELECT_ENTER,
    TXT_SELECT_SINGLE,
    TXT_SELECT_TWO,
    TXT_SELECT_SERVER,
    TXT_SELECT_CLIENT,

    TXT_PAUSE_PAUSE,
    TXT_PAUSE_MUSIC,
    TXT_PAUSE_SOUND,

    TXT_START_SELECT,

    TXT_STOP_WIN,
    TXT_STOP_LOOSE,
    TXT_STOP_NOBODY,
    TXT_STOP_WIN_1,
    TXT_STOP_WIN_2,
    TXT_STOP_RESTART,
    TXT_STOP_MENU,

    // Internet texts
    TXT_INTERNET_TURN,
    TXT_INTERNET_WAIT,
    // Server massages
    TXT_SERVER_WAIT,
    TXT_SREVER_PORT,
    // Client messages
    TXT_CLIENT_IP,
    TXT_CLIENT_PORT,
    TXT_CLIENT_CONNECT,
    TXT_CLIENT_START
};
#define TXT_count 24

// Declaring static text
extern GUI::staticText texts[TXT_count];

// Declaring global list of animations
#if ANI_count
extern Animation Advertisment[ANI_count];
#endif

extern GUI::Button esc;

// External values to save and load from settings file
extern LNG_types language;  // Language settings
extern Uint8 MusicVolume;  // Start volume of music
extern Uint8 EffectsVolume;  // Start volume of effects
extern Uint16 drawFPS;  // Setted frames per seconds
