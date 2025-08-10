/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "libraries.hpp"
#include "initFile.hpp"
#include "preloaded/sounds.hpp"
#include "preloaded/music.hpp"
#include "window.hpp"


// Class of whole current application
class App : Libraries {
 private:
    // Flags of work
    static bool running;

 public:
    App();
    // Commands to operate with global running
    static void stop();
    static bool isRunning();
};

extern App app;
