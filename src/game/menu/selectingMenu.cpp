/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "selectingMenu.hpp"
#include "../../data/cycleTemplate.hpp"


bool SelectingMenu::active = false;

SelectingMenu::SelectingMenu(const Window& _window)
: startFields(_window),
savedFields(_window),
backplate(_window, 0.5, 0.5, 0.8, 0.7, 40, 4),
continueButton(_window, 0.5, 0.35, {"Continue", "Продолжить", "Fortfahren", "Прадоўжыць"}),
startNewButton(_window, 0.5, 0.48, {"Create new", "Создать", "Schaffen", "Стварыць"}),
loadButton(_window, 0.5, 0.61, {"Load", "Загрузить", "Hochladen", "Загрузіць"}),
exitButton(_window, 0.5, 0.75, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}) {}

void SelectingMenu::activate() {
    active ^= true;
    startFields.reset();
    savedFields.reset();
}

void SelectingMenu::reset() {
    active = false;
}

void SelectingMenu::open() {
    active = true;
}

bool SelectingMenu::isActive() {
    return active;
}

void SelectingMenu::addField(const Field& _field) {
    savedFields.addFieldRuntime(_field);
}

const Field* SelectingMenu::click(const Mouse _mouse) {
    // If in menu
    if (active) {
        // Check, if selecting new field
        if (startFields.isActive()) {
            // Check, if select
            return startFields.click(_mouse);
        }
        // Check, if loading fields
        if (savedFields.isActive()) {
            // Check, if select
            return savedFields.click(_mouse);
        }
        // In menu checks
        // Check for game start
        if (continueButton.in(_mouse)) {
            // Closing that menu
            active = false;
            return nullptr;
        }
        if (startNewButton.in(_mouse)) {
            // Starting selecting new field from avaliable
            startFields.activate();
            return nullptr;
        }
        if (loadButton.in(_mouse)) {
            // Starting selecting field from previous games
            savedFields.activate();
            return nullptr;
        }
        if (exitButton.in(_mouse)) {
            // Going to menu
            CycleTemplate::stop();
            return nullptr;
        }
    }
    return nullptr;
}

void SelectingMenu::scroll(float _wheelY) {
    if (active) {
        if (_wheelY > 0) {
            for (;_wheelY > 0; --_wheelY) {
                savedFields.moveUp();
            }
        } else {
            for (;_wheelY < 0; ++_wheelY) {
                savedFields.moveDown();
            }
        }
    }
}

void SelectingMenu::escape() {
    // Closing top object
    if (startFields.isActive()) {
        startFields.reset();
        return;
    }
    if (savedFields.isActive()) {
        savedFields.reset();
        return;
    }
    active = false;
}

void SelectingMenu::blit() const {
    // Bliting waiting menu
    if (active) {
        // Bliting end background
        backplate.blit();

        // Blitting buttons
        continueButton.blit();
        startNewButton.blit();
        loadButton.blit();
        exitButton.blit();

        // Blitting start variants
        startFields.blit();
        savedFields.blit();
    }
}
