#pragma once

// Loading initialasing settings in game
void loadInitFile();

// Saving initialasing file
void saveInitFile();

// Macroses to set min/max values
#define SET_MIN(value, min) (value = value < min ? min : value)
#define SET_MAX(value, max) (value = value > max ? max : value)