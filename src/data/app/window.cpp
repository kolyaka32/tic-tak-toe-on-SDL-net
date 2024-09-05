/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "window.hpp"
#include "../../define.hpp"
#include "../exceptions.hpp"

// Realisations of window class functions
Window::Window(int _width, int _height) {
    // Creating window
    window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, _width, _height, 0);
    #if CHECK_CORRECTION
    if (window == NULL) {
        throw LibararyLoadException("window creation");
    }
    #endif

    // Creating renderer from window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #if CHECK_CORRECTION
    if (renderer == NULL) {
        throw LibararyLoadException("renderer creation");
    }
    #endif
}

Window::~Window() {
    // Destroying renderer
    SDL_DestroyRenderer(renderer);

    // Destrying window
    SDL_DestroyWindow(window);
}

SDL_Renderer* Window::getRender() {
    return renderer;
}

SDL_Window* Window::getWindow() {
    return window;
}

SDL_Texture** Window::getTextures() {
    return textures.getTextures();
}

void Window::updateTitle(language _lang) {
    
}
