/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "saveInfo.hpp"


// Class for store all game saves and load it, when need
class GameSaves {
private:
    static std::vector<Field> startOptions;

    // Draw options
    const Window& window;
    int selected;
    std::vector<SDL_Texture*> images;

public:
    GameSaves(const Window& window);
    ~GameSaves();
    void click(const Mouse mouse);
    void blit() const;

    // Work with global saves
    static void addField();
    static void saveAll();
};
