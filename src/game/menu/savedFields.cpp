/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "savedFields.hpp"


std::vector<Field> SavedFields::startOptions{};
bool SavedFields::active = false;
int SavedFields::startField = 0;
int SavedFields::endField = 0;

SavedFields::SavedFields(const Window& _window)
: Template(_window),
backplate(_window, 0.5, 0.51, 0.92, 0.8, 20, 4),
emptySavesText(_window, 0.5, 0.5, {"No saves", "Нет сохранений", "Keine Speicherung", "Няма захаванняў"}, 1),
exitButton(_window, 0.5, 0.81, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {
    // Creating options to start
    for (int i=0; i < startOptions.size(); ++i) {
        saveInfos.push_back(new SaveInfo(window, startOptions[i], startOptions.size() - i - 1));
    }
}

SavedFields::~SavedFields() {
    for (int i=0; i < startOptions.size(); ++i) {
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
    if (exitButton.in(_mouse)) {
        active = false;
        return nullptr;
    }
    for (int i=startField; i < endField; ++i) {
        if (saveInfos[i]->in(_mouse)) {
            // Making sound
            sounds.play(Sounds::Reset);
            music.startFromCurrent(Music::MainCalm);
            // Setting new field
            active = false;
            return &startOptions[i];
        }
    }
    return nullptr;
}

void SavedFields::moveUp() {
    // Check, if can scroll up
    if (endField < saveInfos.size()) {
        startField++;
        endField++;
        for (int i=0; i < saveInfos.size(); ++i) {
            saveInfos[i]->moveDown();
        }
    }
}

void SavedFields::moveDown() {
    // Check, if can scroll down
    if (startField > 0) {
        startField--;
        endField--;
        for (int i=0; i < saveInfos.size(); ++i) {
            saveInfos[i]->moveUp();
        }
    }
}

void SavedFields::blit() const {
    if (active) {
        backplate.blit();
        // Check, if has fields
        if (endField) {
            for (int i=startField; i < endField; ++i) {
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

    // Check, if add, when has place
    if (endField < maxFieldNumber) {
        // Moving all infos
        for (int i=0; i < saveInfos.size(); ++i) {
            saveInfos[i]->moveDown();
        }
        // Creating new
        saveInfos.push_back(new SaveInfo(window, _field, 0));
        endField++;
    } else {
        // Check, if need to save current position in list
        if (endField == saveInfos.size()) {
            // Moving all down
            for (int i=0; i < saveInfos.size(); ++i) {
                saveInfos[i]->moveDown();
            }
            // Creating new
            saveInfos.push_back(new SaveInfo(window, _field, 0));
            endField++;
            startField++;
        } else {
            // Placing and not showing
            saveInfos.push_back(new SaveInfo(window, _field, startField-endField));
        }
    }
}


// Static objects
void SavedFields::addField(const Field& _field) {
    startOptions.push_back(_field);
}

void SavedFields::addField(const std::string _saveText) {
    // Check on size (has need byte of size and fit correctly)
    if (_saveText.size() > 4 && _saveText.size() == Field::getSaveSize(_saveText[1]-'0')) {
        // Create field
        startOptions.push_back(Field(_saveText.c_str()));
        // Check control sum
        if (startOptions[startOptions.size()-1].getCheckSum() != _saveText[0]) {
            startOptions.pop_back();
            return;
        }
        // Adding to counter
        if (endField >= maxFieldNumber) {
            startField++;
        }
        endField++;
    }
}

void SavedFields::saveFields(std::ofstream& _fout) {
    for (auto f : startOptions) {
        _fout << "save = ";
        const Array<char> save = f.getSave();
        _fout.write(save.getData(), save.getSize());
        _fout << '\n';
    }
}
