/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../cyclesNames.hpp"
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
    // Next cycle, that will be run
    static Cycle nextCycle;
    // Option for compact launch of cycle
    template <class Cycle>
    static void runCycle(Window& window);

 public:
    // Commands to operate with global running
    static void stop();
    static bool isRunning();
    static void startNext(const Cycle nextCycle);
    static void run(Window& window);
};

template <class Cycle>
void App::runCycle(Window& _window) {
   // Create new cycle
   Cycle cycle{_window};
   // Running it
   cycle.run();
   // Deleting it
}
