/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <fstream>
#include <vector>
#include "saveInfo.hpp"


// Class for store all game saves and load it, when need
class SavedFields : GUI::Template {
 private:
    static std::vector<Field> startOptions;

    // Draw options
    static bool active;
    static int startField;
    static int endField;
    static const int maxFieldNumber = 3;
    GUI::RoundedBackplate backplate;
    std::vector<SaveInfo*> saveInfos;
    GUI::HighlightedStaticText emptySavesText;
    GUI::TextButton exitButton;

 public:
    explicit SavedFields(const Window& window);
    ~SavedFields();
    void activate();
    bool isActive();
    void reset();
    const Field* click(const Mouse mouse);
    void moveUp();
    void moveDown();
    void blit() const override;

    // Work with global saves
    void addFieldRuntime(const Field& field);  // Add another field during runtime
    static void addField(const Field& field);
    static void addField(const std::string saveText);
    static void saveFields(std::ofstream& stream);
};
