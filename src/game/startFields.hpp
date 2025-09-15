/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "field.hpp"


// Options for
class StartFields {
 private:
    // Start variants
    static Field startOptions[4];

    // Graphical interface for selecting
    static bool active;
    GUI::RoundedBackplate backplate;
    GUI::TextButton optionButton[4];
    GUI::TextButton closeButton;

 public:
    StartFields(const Window& window);

    void activate();
    bool isActive();
    void reset();

    const Field* click(const Mouse mouse);

    void blit() const;
};
