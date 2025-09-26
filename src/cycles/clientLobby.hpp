/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../internet/client.hpp"


// Game cycle (for single player (special animation))
class ClientLobbyCycle : public BaseCycle {
 private:
    // Internet parameters
    Client client;

    // Input fields
    GUI::StaticText enterIPText;
    GUI::TypeBox<15> enterIPField;
    GUI::StaticText enterPortText;
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
    explicit ClientLobbyCycle(Window& _window);
};
