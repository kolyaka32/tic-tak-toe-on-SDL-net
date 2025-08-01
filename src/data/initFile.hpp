/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../soundsNames.hpp"
#include "../musicNames.hpp"


// Class for load/save settings to/from game
class InitFile {
 private:
    Music& music;
    Sounds& sounds;
    const std::string getText(const std::string line) const;
    const unsigned getValue(const std::string line) const;

 public:
    InitFile(Music& music, Sounds& sounds);
    ~InitFile();
    void loadSettings();
    void saveSettings();
};
