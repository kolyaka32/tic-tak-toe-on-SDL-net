/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "startFields.hpp"
#include "savedFields.hpp"


// 
class GameMenu {
 private:
    bool active = false;

    StartFields startFields;
    SavedFields savedFields;

    // Menu after game end
    GUI::RoundedBackplate backplate;
    GUI::TextButton continueButton;
    GUI::TextButton startNewButton;
    GUI::TextButton loadButton;
    GUI::TextButton exitButton;

 public:
    explicit GameMenu(const Window& window);
    void activate();
    bool isActive() const;
    void addField(const Field& field);
    const Field* click(const Mouse mouse);
    void scroll(float wheelY);
    void blit() const;
};
