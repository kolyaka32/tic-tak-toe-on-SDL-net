/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Class with message box, showing information at center of screen
class TerminatedBox {
private:
    static bool active;

    // Main text
    const GUI::HighlightedStaticText mainText;
    // Button for close this box
    const GUI::TextButton closeButton;
    // Background plate for better visability
    const GUI::Backplate background;

public:
    TerminatedBox();
    bool click(const Mouse mouse);
    void blit() const;
    static void activate();
    static void reset();
    static bool isActive();
};
