/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include <array>
#include "saveInfo.hpp"


// Class for store all game saves and load it, when need
class SavedFields : GUI::Template {
 private:
    static std::vector<Field> startOptions;

    // Draw options
    static bool active;
    const int maxFieldNumber = 3;
    int fieldNumber;
    GUI::RoundedBackplate backplate;
    std::array<SaveInfo*, 3> saveInfos;
    GUI::HighlightedStaticText emptySavesText;
    GUI::TextButton exitButton;

 public:
    SavedFields(const Window& window);
    ~SavedFields();
    void activate();
    bool isActive();
    void reset();
    const Field* click(const Mouse mouse);
    void blit() const override;

    // Work with global saves
    void addFieldRuntime(const Field& field);  // Add another field during runtime
    static void addField(const Field& field);
    static void saveAll();
};
