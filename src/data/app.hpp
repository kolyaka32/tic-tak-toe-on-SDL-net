/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "preloaded/sounds.hpp"
#include "preloaded/music.hpp"
#include "window.hpp"
#include "mouse.hpp"
#include "macroses.hpp"


// Class of whole current application
class App {
 private:
    // Flags of work
    static bool running;

 public:
    // Commands to operate with global running
    static void stop();
    static bool isRunning();
};
