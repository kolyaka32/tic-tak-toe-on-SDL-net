/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "savedFields.hpp"


std::vector<Field> SavedFields::startOptions{};
bool SavedFields::active = false;

SavedFields::SavedFields(const Window& _window)
: Template(_window),
backplate(_window, 0.5, 0.51, 0.9, 0.8, 20, 4),
emptySavesText(_window, 0.5, 0.5, {"No saves", "Нет сохранений", "Keine Speicherung", "Няма захаванняў"}, 1),
exitButton(_window, 0.5, 0.81, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {
    // Resetting
    for (int i=0; i < maxFieldNumber; ++i) {
        saveInfos[i] = nullptr;
    }
    // Creating options to start
    fieldNumber = min(startOptions.size(), size_t(maxFieldNumber));
    for (int i=0; i < fieldNumber; ++i) {
        saveInfos[i] = new SaveInfo(window, startOptions[fieldNumber - i - 1], i);
    }
}

SavedFields::~SavedFields() {
    // ! Need to check on correct clearance of saveInfos
    for (int i=0; i < fieldNumber; ++i) {
        delete saveInfos[i];
    }
}

void SavedFields::activate() {
    active = true;
}

bool SavedFields::isActive() {
    return active;
}

void SavedFields::reset() {
    active = false;
}

const Field* SavedFields::click(const Mouse _mouse) {
    if (active) {
        if (exitButton.in(_mouse)) {
            active = false;
            return nullptr;
        }
        for (int i=0; i < fieldNumber; ++i) {
            if (saveInfos[i]->in(_mouse)) {
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
                saveInfos[i]->blit();
            }
        } else {
            emptySavesText.blit();
        }
        exitButton.blit();
    }
}

void SavedFields::addFieldRuntime(const Field& _field) {
    // Add to global list
    addField(_field);

    // Check, if need to add new one
    if (fieldNumber < maxFieldNumber) {
        fieldNumber++;
    } else {
        // Clear last info
        delete saveInfos[maxFieldNumber-1];
    }
    // Moving all infos
    for (int i=fieldNumber-1; i > 0; --i) {
        saveInfos[i] = saveInfos[i-1];
        saveInfos[i]->moveDown();
    }
    // Creating new
    saveInfos[0] = new SaveInfo(window, _field, 0);
}


// Static objects
void SavedFields::addField(const Field& _field) {
    startOptions.push_back(_field);
    //startOptions[0] = _field;
}

void SavedFields::saveAll() {

}
