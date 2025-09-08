/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>
#include "logger.hpp"
#include "../languagesNames.hpp"


// Class, storing one text variant in different locations
class LanguagedText {
 private:
    static Language currentLanguage;
    const std::string textVariants[(unsigned)Language::Count];

 public:
    LanguagedText(const std::string englishVariant, const std::string russianVariant,
        const std::string germanVariant, const std::string bellarussianVariant);
    LanguagedText(const std::string singleVariant);
    const std::string& getString() const;
    // Options for change current language
    static bool setLanguage(Language newLanguage);
    static Language getLanguage();
};
