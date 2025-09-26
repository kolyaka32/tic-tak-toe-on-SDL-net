/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"
#include "macroses.hpp"
#include "exceptions.hpp"


// Check if has initfile
#if (USE_SETTING_FILE)
#include <string>


// Class for load/save settings to/from game
class InitFile {
 private:
    const std::string getText(const std::string line) const;
    const unsigned getValue(const std::string line) const;

 public:
    InitFile();
    ~InitFile();
    void loadSettings();
    void saveSettings();
};

#endif  // (USE_SETTING_FILE)
