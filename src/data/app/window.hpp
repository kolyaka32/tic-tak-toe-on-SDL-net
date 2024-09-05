/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "SDL.h"
#include "../loading/graphics.hpp"
#include "../languages.hpp"

// Class for window, where to draw
class Window {
 private:
    SDL_Renderer *renderer;  // Renderer for draw any objects at screen
    SDL_Window *window;      // Main window, where objects draw to
    Textures textures{texturesFilesNames, renderer};  // List with all
 public:
    // Create window with need width and height
    Window(int width, int height);
    ~Window();
    SDL_Renderer* getRender();
    SDL_Window* getWindow();
    SDL_Texture** getTextures();
    virtual void updateTitle(language lang);
};
