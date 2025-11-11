/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <thread>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>
#include "idleTimer.hpp"
#include "app.hpp"


// Template for any cycles
class CycleTemplate {
 private:
    static bool running;     // Flag of current running state
    static bool restarting;  // Flag, if game was restarted

    // Internal cycles of work
    // Cycle for separated thread to get any input
    void inputCycle();
    IdleTimer inputTimer{1000/60};  // Timer to idle properly
    // Cycle for separated thread to draw
    void drawCycle();
    IdleTimer drawTimer{1000/60};  // Timer to idle properly
    std::thread drawThread{drawCycle, this};  // Threads itself

 protected:
    Window& window;  // Target, where draw to

    // Start options
    void startNext(const Cycle nextCycle);

    // Cycle functions for cycle (could be overriden)
    virtual void update();  // Getting special objects update
    virtual void draw();    // Draw all need objects

    // Subprograms for get need input
    virtual bool inputMouseDown();                // Actioning for mouse button pressing
    virtual void inputMouseUp();                  // Actioning for mouse button unpressing
    virtual void inputKeys(SDL_Keycode key);      // Actioning for any keys pressing
    virtual void inputMouseWheel(float wheelY);   // Actioning for scrolling wheel
    virtual void inputText(const char* text);     // Actioning for typing text

 public:
    CycleTemplate(Window& window);
    void run();
    // Function for stop current running cycle
    static void stop();
    static bool isRunning();
    static void restart();
    static bool isRestarted();
};
