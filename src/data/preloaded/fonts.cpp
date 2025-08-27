/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "fonts.hpp"

// Check, if use fonts and preload it
#if (USE_SDL_FONT) && (PRELOAD_FONTS)

#include "loader/loader.hpp"
#include "../exceptions.hpp"


FontsData::FontsData() {
    // Resetting fonts array
    #if CHECK_CORRECTION
    for (unsigned i=0; i < unsigned(Fonts::Count); ++i) {
        fonts[i] = nullptr;
    }
    #endif

    // Loading all needed fonts
    for (unsigned i=0; i < unsigned(Fonts::Count); ++i) {
        loadFont(Fonts(i), fontsFilesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < unsigned(Fonts::Count); ++i) {
        if (fonts[i] == NULL) {
            throw DataLoadException(fontsFilesNames[i]);
        }
    }
    logAdditional("Fonts loaded corretly");
    #endif
}

FontsData::~FontsData() {
    // Closing all used fonts
    for (unsigned i=0; i < unsigned(Fonts::Count); ++i) {
        TTF_CloseFont(fonts[i]);
    }
}

void FontsData::loadFont(Fonts _index, const char* _fileName) {
    SDL_IOStream* iodata = dataLoader.load(_fileName);

    fonts[unsigned(_index)] = TTF_OpenFontIO(iodata, true, 20.);

    // Checking correction of loaded font
    #if CHECK_CORRECTION
    if (fonts[unsigned(_index)] == nullptr) {
        throw DataLoadException(_fileName);
    }
    #endif
}

TTF_Font* FontsData::operator[](Fonts _index) const {
    return fonts[unsigned(_index)];
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
