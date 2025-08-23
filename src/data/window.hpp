/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "colors.hpp"
#include "mouse.hpp"
#include "time.hpp"
#include "preloaded/textures.hpp"
#include "preloaded/fonts.hpp"
#include "languages.hpp"


// Class of window, where all happen
class Window {
 private:
    int width, height;
    const LanguagedText titleText;
    SDL_Window* window;
    SDL_Renderer* renderer;
    const TexturesData textures;
    const FontsData fonts;

    // Set new title
    void updateTitle(const char* name) const;

 public:
    Window(int width, int height, const LanguagedText title);
    ~Window() noexcept;

    // Functions for work with graphics
    // Operate with sizes of window
    int getWidth() const;
    int getHeight() const;
    void setWidth(int width);
    void setHeight(int height);
    // Set current draw color
    void setDrawColor(Color color = EMPTY) const;
    // Clear all stage with setted color
    void clear() const;
    // Render all buffered objects to screen
    void render() const;

    // Draw simple geometric figures
    void drawPoint(float x, float y) const;
    void drawRect(const SDL_FRect& rect) const;
    void drawLine(float x1, float y1, float x2, float y2) const;

    // Work with loaded data
    SDL_Texture* getTexture(Textures name) const;

    // Work with own surfaces
    SDL_Surface* createSurface(int width, int height, SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32) const;
    void setBlendMode(SDL_Surface* surface, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE) const;
    void destroy(SDL_Surface* surface) const;

    // Work with loaded textures
    void blit(Textures index, const SDL_FRect& dest) const;
    void blit(Textures index, const SDL_FRect* dest = nullptr, const SDL_FRect* src = nullptr) const;
    void blit(Textures index, float angle, const SDL_FRect& rect, const SDL_FRect* src = nullptr,
        SDL_FPoint center = {0, 0}) const;
    void setBlendMode(Textures index, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE) const;
    void setColorMode(Textures index, Color color = EMPTY) const;

    // Work with own textures
    SDL_Texture* createTexture(int width, int height, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET,
        SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32) const;
    SDL_Texture* createTexture(SDL_Surface* surface) const;
    SDL_Texture* createTextureAndFree(SDL_Surface* surface) const;
    void blit(SDL_Texture* texture, const SDL_FRect& dest) const;
    void blit(SDL_Texture* texture, const SDL_FRect* dest, const SDL_FRect* src) const;
    void blit(SDL_Texture* texture, float angle, const SDL_FRect& rect, const SDL_FRect* src = nullptr,
        SDL_FPoint center = {0, 0}) const;
    void setRenderTarget(SDL_Texture* target) const;
    void resetRenderTarget() const;
    void setBlendMode(SDL_Texture* texture, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE) const;
    void setColorMode(SDL_Texture* texture, Color color = EMPTY) const;
    void unlock(SDL_Texture* texture) const;
    void destroy(SDL_Texture* texture) const;

    // Work with fonts and text
    TTF_Font* getFont(Fonts name) const;
    TTF_Font* createFontCopy(Fonts name, float height) const;
    SDL_Texture* createTexture(Fonts font, float height, const char* text, unsigned length, Color color) const;
    SDL_Texture* createTexture(TTF_Font* font, const char* text, Color color) const;

    // Work with window
    void startTextInput() const;
    void stopTextInput() const;
    void updateTitle() const;
};
