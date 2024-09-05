/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */


#include "window.hpp"

// Indexes of windows
enum WINDOWS_names {
    WIN_MAIN,  // Main window with
};



// Class of system for all drawings
class Screen {
private:
    // All windows
    // Array of all windows, where to draw
    MainWindow mainWindow;

    // Active drawing objects
    SDL_Renderer *renderer;  // Renderer for draw objects at current screen
    SDL_Window *window;      // Window, for editing
    SDL_Texture **textures;  // List with all textures

public:
    Screen();
    Screen(unsigned fieldWidth);

    // Draw need sprite at need place
    void draw(SDL_Texture* texture, const SDL_Rect* dst = NULL, const SDL_Rect* src = NULL);
    // Draw need texture (from list)
    void draw(unsigned index, const SDL_Rect* dst = NULL, const SDL_Rect* src = NULL);
    // Draw need sprite at need place (rotated)
    void draw(SDL_Texture* texture, float angle, const SDL_Rect* dst = NULL,
        const SDL_Point* centerRotation = NULL, const SDL_Rect* src = NULL);
    // Draw need sprite (from list) at need place (rotated)
    void draw(unsigned index, float angle, const SDL_Rect* dst = NULL,
        const SDL_Point* centerRotation = NULL, const SDL_Rect* src = NULL);
    // Fill rect with selected color
    void fillRect(const SDL_Rect& rect);
    // Fill float rect with selected color
    void fillRect(const SDL_FRect& rect);
    // Draw point at need position
    void drawPoint(int x, int y);
    // Blitting all buffered objects
    void render();
    // Changing color for draw
    void setColor(const SDL_Color& color);
    // Set (or reset) target, where to draw
    void setRenderTarget(SDL_Texture* target = nullptr);
    // Create texture from surface
    SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
    // Operating with window
    // Getting current window width
    int getWindowWidth();
    // Getting current window height
    int getWindowHeight();
    // Changing title of window
    void setTitle(const char* title);
    // Show system text box with need parameters
    void showTextBox(const char *title, const char *message, Uint32 flag = SDL_MESSAGEBOX_INFORMATION);

    // Functions for change active window to draw
    void changeWindow(Uint8 windowIndex = 0);
};
