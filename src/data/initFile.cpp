/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "initFile.hpp"


// Check if has initfile
#if (USE_SETTING_FILE)

InitFile::InitFile() {
    loadSettings();
}

InitFile::~InitFile() {
    saveSettings();
}

const std::string InitFile::getText(const std::string _line) const {
    return _line.substr(_line.rfind('=') + 2);
}

const unsigned InitFile::getValue(const std::string _line) const {
    return std::stoi(_line.substr(_line.rfind('=') + 2));
}

#endif  // (USE_SETTING_FILE)
