/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"


// Static class members
bool CycleTemplate::running;
bool CycleTemplate::restarting;

// Reset basic cycle template variables
CycleTemplate::CycleTemplate(Window& _window)
: window(_window) {
    // Resetting input
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {}
    running = true;
}

void CycleTemplate::stop() {
    running = false;
}

bool CycleTemplate::isRunning() {
    return running;
}

void CycleTemplate::restart() {
    restarting = true;
    running = false;
}

bool CycleTemplate::isRestarted() {
    return restarting;
}

void CycleTemplate::startNext(const Cycle _nextCycle) {
    App::startNext(_nextCycle);
    stop();
}

void CycleTemplate::inputCycle() {
    logAdditional("Start input cycle");
    // Running loop with inputting
    while (isRunning()) {
        // Creating event for get user input
        SDL_Event event;

        // Getting input
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            // Code of program exiting
            case SDL_EVENT_QUIT:
                // Stopping program at all
                App::stop();
                return;

            // Getting mouse input
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                inputMouseDown();
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                inputMouseUp();
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                inputMouseWheel(event.wheel.y);
                break;

            // Getting keys presses
            case SDL_EVENT_KEY_DOWN:
                inputKeys(event.key.key);
                break;

            // Text inputing
            case SDL_EVENT_TEXT_INPUT:
                inputText(event.text.text);
                break;
            }
        }

        // Waiting
        inputTimer.sleep();
    }
}

void CycleTemplate::drawCycle() {
    // Waiting, until can run this
    App::waitStart();

    logAdditional("Start draw cycle");

    // Running draw cycle
    while (isRunning()) {
        // Drawing objects
        draw();

        // Waiting
        drawTimer.sleep();
    }
}


// Empty templates
void CycleTemplate::draw() {}

void CycleTemplate::update() {}

bool CycleTemplate::inputMouseDown() {
    return false;
}

void CycleTemplate::inputMouseUp() {}

// Example for getting keys input
void CycleTemplate::inputKeys(SDL_Keycode _key) {
    /*switch (_key) {
    case SDLK_ESCAPE:
        // Stopping ruuning by escape
        running = false;
        return;
    }*/
}

// Example for getting mouse wheel input
void CycleTemplate::inputMouseWheel(float _wheelY) {
    // if (MusicSlider.scroll(event.wheel.y, mouse));
    // else if (SoundSlider.scroll(event.wheel.y, mouse));
}

// Example for getting text input
void CycleTemplate::inputText(const char* text) {
    // typeBox.writeString(event.text.text);
}

// Function for start need cycle
void CycleTemplate::run() {
    // Resetting restart flag after all started
    restarting = false;

    // Allowing other cycles to start
    App::start();

    // Starting input cycle
    inputCycle();
}
