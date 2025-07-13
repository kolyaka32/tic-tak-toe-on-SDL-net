
#include "screen.hpp"

Screen::Screen() : mainWindow(10) {
    renderer = mainWindow.getRender();
    window = mainWindow.getWindow();
    textures = mainWindow.getTextures();
}

Screen::Screen(unsigned fieldWidth) : mainWindow(fieldWidth) {
    renderer = mainWindow.getRender();
    window = mainWindow.getWindow();
    textures = mainWindow.getTextures();
}

void Screen::draw(SDL_Texture* _texture, const SDL_Rect* _dst, const SDL_Rect* _src) {
    SDL_RenderCopy(renderer, _texture, _src, _dst);
}

void Screen::draw(unsigned _index, const SDL_Rect* _dst, const SDL_Rect* _src) {
    SDL_RenderCopy(renderer, textures[_index], _src, _dst);
}

void Screen::draw(SDL_Texture* _texture, float _ang, const SDL_Rect* _dst,
    const SDL_Point* _cen, const SDL_Rect* _src) {
    SDL_RenderCopyEx(renderer, _texture, _src, _dst, _ang, _cen, SDL_FLIP_NONE);
}

void Screen::draw(unsigned _index, float _ang, const SDL_Rect* _dst,
    const SDL_Point* _cen, const SDL_Rect* _src) {
    SDL_RenderCopyEx(renderer, textures[_index], _src, _dst, _ang, _cen, SDL_FLIP_NONE);
}

void Screen::fillRect(const SDL_Rect& _rect) {
    SDL_RenderFillRect(renderer, &_rect);
}

void Screen::fillRect(const SDL_FRect& _rect) {
    SDL_RenderFillRectF(renderer, &_rect);
}

void Screen::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void Screen::render() {
    SDL_RenderPresent(renderer);
}

void Screen::setColor(const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Screen::setRenderTarget(SDL_Texture* target) {
    SDL_SetRenderTarget(renderer, target);
}

SDL_Texture* Screen::createTextureFromSurface(SDL_Surface* surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}

int Screen::getWindowWidth() {
    int width;
    SDL_GetWindowSize(window, &width, nullptr);
    return width;
}

int Screen::getWindowHeight() {
    int height;
    SDL_GetWindowSize(window, nullptr, &height);
    return height;
}

void Screen::setTitle(const char* title) {
    SDL_SetWindowTitle(window, title);
}

void Screen::showTextBox(const char *title, const char *message, Uint32 flag) {
    SDL_ShowSimpleMessageBox(flag, title, message, window);
}

void Screen::changeWindow(Uint8 windowIndex) {
    switch (windowIndex) {
    case 0:
        // Code of main window
        renderer = mainWindow.getRender();
        window = mainWindow.getWindow();
        textures = mainWindow.getTextures();
        break;
    
    default:
        // Unknown window type
        break;
    }
}
