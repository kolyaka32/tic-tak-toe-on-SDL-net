/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "app/libraries.hpp"
#include "app/initFile.hpp"
#include "app/screen.hpp"


// Main process
class App : Libraries {
public:
	App();

    // Loaded file with all starting data
    InitFile initFile;

    // Drawing system
    Screen screen;
};

// Current application
extern App app;
