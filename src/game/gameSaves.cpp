/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameSaves.hpp"


std::vector<Field> GameSaves::startOptions{};

GameSaves::GameSaves(const Window& _window)
: window(_window) {
    images.reserve(startOptions.size());

    // Creating images
    for (int i=0; i < startOptions.size(); ++i) {
        ;
        images[i] = window.createTexture(startOptions[i]*);
    }
}

GameSaves::~GameSaves() {
    for (int i=0; i < images.size(); ++i) {
        SDL_DestroyTexture(images[i]);
    }
}

void GameSaves::click(const Mouse mouse) {

}

void GameSaves::blit() const {

}


// Static objects
void GameSaves::addField() {

}

void GameSaves::saveAll() {

}
