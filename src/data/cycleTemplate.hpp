/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>
#include "idleTimer.hpp"
#include "app.hpp"


// Template for any cycles
class CycleTemplate {
 private:
    static bool running;            // Flag of current running state
    static bool restarting;         // Flag, if game was restarted
    static bool additionalRestart;  // Flag of additional game restart
    IdleTimer idleTimer{1000/60};   // Timer to idle in main cycle

 protected:
    Window& window;  // Target, where draw to
    Mouse mouse;     // Position of mouse on screen

    // Cycle functions for cycle (should be overriden)
    void getInput();            // Getting all user input
    virtual void update();      // Getting special objects update
    virtual void draw() const;  // Draw all need objects

    // Subprograms for get need input
    virtual bool inputMouseDown();                // Actioning for mouse button pressing
    virtual void inputMouseUp();                  // Actioning for mouse button unpressing
    virtual void inputKeys(SDL_Keycode key);      // Actioning for any keys pressing
    virtual void inputMouseWheel(float _wheelY);  // Actioning for scrolling wheel
    virtual void inputText(const char* text);     // Actioning for typing text

 public:
    CycleTemplate(Window& window);
    void run();
    // Function for stop current running cycle
    static void stop();
    static void restart();
    static bool isRestarted();
    static bool isAdditionalRestarted();
    // Function for starting new cycle with posible arguments
    template <class NewCycle, typename ...Args>
    static void runCycle(Window& window, const Args& ...args);
};


template <class NewCycle, typename ...Args>
void CycleTemplate::runCycle(Window& _window, const Args& ...args) {
    restarting = false;
    additionalRestart = false;

    // Running current cycle, while restarting
    do {
        // Launching new cycle
        NewCycle cycle(_window, args...);
        cycle.run();
    } while (App::isRunning() && (restarting | additionalRestart));

    // Restarting external running cycle for correct language change
    restarting = false;
    additionalRestart = true;
    running = false;
}
