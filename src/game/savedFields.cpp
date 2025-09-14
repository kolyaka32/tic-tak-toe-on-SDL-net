/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "savedFields.hpp"


std::vector<Field> SavedFields::startOptions{};

SavedFields::SavedFields(const Window& _window)
: Template(_window),
backplate(_window, 0.5, 0.5, 0.8, 0.8, 20, 4),
emptySavesText(_window, 0.5, 0.5, {"No saves", "Нет сохранений", "Keine Speicherung", "Няма захаванняў"}, 1),
exitButton(_window, 0.5, 0.8, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {
    fieldNumber = min(startOptions.size(), size_t(5));
    saveInfos.reserve(fieldNumber);
    // Creating options to start
    for (int i=0; i < fieldNumber; ++i) {
        saveInfos.push_back(SaveInfo(window, startOptions[i], i));
    }
}

SavedFields::~SavedFields() {
    // ! Need to check on correct clearance of saveInfos
    saveInfos.clear();
}

void SavedFields::activate() {
    active = true;
}

bool SavedFields::isActive() {
    return active;
}

const Field* SavedFields::click(const Mouse _mouse) {
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

void SavedFields::blit() const {
    if (active) {
        backplate.blit();
        // Check, if has fields
        if (fieldNumber) {
            for (int i=0; i < fieldNumber; ++i) {
                saveInfos[i].blit();
            }
        } else {
            emptySavesText.blit();
        }
        exitButton.blit();
    }
}


// Static objects
void SavedFields::addField() {

}

void SavedFields::saveAll() {

}
