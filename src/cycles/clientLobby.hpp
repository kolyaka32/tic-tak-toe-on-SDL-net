/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"


// Game cycle (for single player (special animation))
class ClientLobbyCycle : public BaseCycle {
 private:
    // Input fields
    GUI::StaticText enterIPText;
    static char baseIP[15];
    GUI::TypeBox<15> enterIPField;
    GUI::StaticText enterPortText;
    static char basePort[6];
    GUI::TypeBox<6> enterPortField;
    GUI::TextButton pasteButton;
    GUI::TextButton connectButton;

    void pasteFromClipboard();

    // Main run functions
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputText(const char* text) override;
    void update() override;
    void draw() const override;

 public:
    ClientLobbyCycle(Window& _window);
    ~ClientLobbyCycle();
    static void writeBaseIP(const char* text);
    static const char* getBaseIP();
    static void writeBasePort(const char* text);
    static const char* getBasePort();
};
