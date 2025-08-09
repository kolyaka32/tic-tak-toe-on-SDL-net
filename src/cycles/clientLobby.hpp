/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../internet/client.hpp"


// Global base connect link for type in typeboxes
extern char baseIP[12];
extern char basePort[6];

// Game cycle (for single player (special animation))
class ClientLobbyCycle : public BaseCycle {
 private:
    // Internet parameters
    Client client;

    // Input fields
    GUI::StaticText enterIPText;
    GUI::TypeField<12> enterIPField;
    GUI::StaticText enterPortText;
    GUI::TypeField<6> enterPortField;
    GUI::TextButton connectButton;
    GUI::TextButton pasteButton;

    void pasteFromClipboard();

    // Main run functions
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode key) override;
    void inputText(const char* text) override;
    void update() override;
    void draw() const override;

 public:
    ClientLobbyCycle();
};
