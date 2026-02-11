/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"


// Cycle with waiting for client connect
class ServerLobbyCycle : public BaseCycle {
 private:
    // Title
    GUI::HighlightedStaticText titleText;

    // Text with current connection address
    static bool showAddress;            // Flag of showing current address to screen
    GUI::StaticText showAddressText;   // Text for showing/copying current address
    GUI::StaticText hideAddressText;    // Text for showing/copying current address
    GUI::InfoBox copiedInfoBox;         // Message about copying to clipboard address
    GUI::TextButton showAddressButton;  // Buttons to change state of showing address at screen
    GUI::TextButton hideAddressButton;  // Button with illustration of address, hidden by stars

    // Main run functions
    bool inputMouseDown() override;
    void update() override;
    void draw() const override;

 public:
    ServerLobbyCycle(Window& window);
};
