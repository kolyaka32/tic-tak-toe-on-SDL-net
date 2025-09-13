/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameSaves.hpp"


std::vector<Field> GameSaves::startOptions{};

GameSaves::GameSaves(const Window& _window)
: Template(_window),
backplate(_window, 0.5, 0.5, 0.8, 0.8, 8, 2),
exitButton(_window, 0.5, 0.8, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {
    fieldNumber = min(startOptions.size(), size_t(5));
    saveInfos.reserve(fieldNumber);
    // Creating options to start
    for (int i=0; i < fieldNumber; ++i) {
        saveInfos.push_back(SaveInfo(window, startOptions[i], i));
    }
}

GameSaves::~GameSaves() {
    // ! Need to check on correct clearance of saveInfos
    saveInfos.clear();
}

void GameSaves::activate() {
    active = true;
}

const Field* GameSaves::click(const Mouse _mouse) {
    if (active) {
        if (exitButton.in(_mouse)) {
            active = false;
            return nullptr;
        }
        for (int i=0; i < fieldNumber; ++i) {
            if (saveInfos[i].in(_mouse)) {
                active = false;
                return &startOptions[i];
            }
        }
    }
    return nullptr;
}

void GameSaves::blit() const {
    if (active) {
        backplate.blit();
        for (int i=0; i < fieldNumber; ++i) {
            saveInfos[i].blit();
        }
        exitButton.blit();
    }
}


// Static objects
void GameSaves::addField() {

}

void GameSaves::saveAll() {

}
