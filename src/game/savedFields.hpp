/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "saveInfo.hpp"


// Class for store all game saves and load it, when need
class SavedFields : GUI::Template {
 private:
    static std::vector<Field> startOptions;

    // Draw options
    bool active = false;
    int fieldNumber;
    GUI::RoundedBackplate backplate;
    std::vector<SaveInfo> saveInfos;
    GUI::HighlightedStaticText emptySavesText;
    GUI::TextButton exitButton;

 public:
    SavedFields(const Window& window);
    ~SavedFields();
    void activate();
    bool isActive();
    const Field* click(const Mouse mouse);
    void blit() const override;

    // Work with global saves
    static void addField();
    static void saveAll();
};
