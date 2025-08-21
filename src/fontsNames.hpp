/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


// Names of fonts
enum class Fonts {
    Main,  // Main using font (now only one)

    // Global counter of all loaded fonts
    Count,
};

// Heights of text (for uniformity)
enum Height : int {
    Title = 40,        // Intuding title
    SubTitle = 28,     // Title in subcycles
    Info = 32,
    Main = 24,         // Main text
    Medium = 20,       //
    TypeBox = Medium,  // Special height for typeboxes
    Small = 12,        // Small text
};

// File names of the corresponding fonts
extern const char* fontsFilesNames[unsigned(Fonts::Count)];
