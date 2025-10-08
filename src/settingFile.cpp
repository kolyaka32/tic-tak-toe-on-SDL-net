/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <fstream>
#include <string>
#include "data/initFile.hpp"

// Check if has initfile
#if (USE_SETTING_FILE)

// Files to setup
#include "data/languages.hpp"
#include "game/gameField.hpp"
#include "cycles/clientLobby.hpp"
#include "game/menu/savedFields.hpp"


// Data, load from setting file
void InitFile::loadSettings() {
    // Reading file
    std::ifstream inSettings(SETTING_FILE);
    // Input string line
    std::string currentLine;

    // Reading file until it end
    while (std::getline(inSettings, currentLine)) {
        std::string parameter = currentLine.substr(0, min(currentLine.find(' '), currentLine.find('=')));

        // Switching between options
        if (parameter == "language") {
            std::string lang = getText(currentLine);
            if (lang == "english") {
                LanguagedText::setLanguage(Language::English);
            } else if (lang == "russian") {
                LanguagedText::setLanguage(Language::Russian);
            } else if (lang == "german") {
                LanguagedText::setLanguage(Language::German);
            } else if (lang == "belarusian") {
                LanguagedText::setLanguage(Language::Bellarusian);
            }
        } else if (parameter == "music") {
            music.setVolume(getValue(currentLine));
        } else if (parameter == "sounds") {
            sounds.setVolume(getValue(currentLine));
        } else if (parameter == "IP") {
            ClientLobbyCycle::writeBaseIP(getText(currentLine).c_str());
        } else if (parameter == "port") {
            ClientLobbyCycle::writeBasePort(getText(currentLine).c_str());
        } else if (parameter == "save") {
            SavedFields::addField(getText(currentLine));
        }
    }
    // Closing reading file
    inSettings.close();
}

// Data, saved to setting file
void InitFile::saveSettings() {
    // Creating output file
    std::ofstream outSettings(SETTING_FILE);

    // Writing data with comments to file
    outSettings << "# Settings of chess game:\n";

    // Writing language
    outSettings << "language = ";
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        outSettings << "english\n";
        break;

    case Language::Russian:
        outSettings << "russian\n";
        break;

    case Language::German:
        outSettings << "german\n";
        break;

    case Language::Bellarusian:
        outSettings << "belarusian\n";
        break;

    default:
        break;
    }

    // Writing music and sounds volumes
    outSettings << "music = " << music.getVolume() << "\n";
    outSettings << "sounds = " << sounds.getVolume() << "\n";

    // Writing internet connection data
    outSettings << "\n# Internet base parameters:\n";
    outSettings << "IP = " << ClientLobbyCycle::getBaseIP() << "\n";
    outSettings << "port = " << ClientLobbyCycle::getBasePort() << "\n";

    // Saving fields
    outSettings << "\n# Saves:\n";
    SavedFields::saveFields(outSettings);
}

#endif  // (USE_SETTING_FILE)
