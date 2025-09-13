/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "startFields.hpp"


Field StartFields::startOptions[4] = {
    {3, 3},
    {5, 4},
    {7, 5},
    {9, 7},
};

StartFields::StartFields(const Window& _window)
: backplate{_window, 0.5, 0.5, 0.7, 0.6, 5, 2},
optionButton {
    {_window, 0.5, 0.51, {"Small field", "Маленькое поле", "Kleines Feld", "Невялікае поле"}},
    {_window, 0.5, 0.64, {"Medium field", "Среднее поле", "Mittleres Feld", "Сярэдняе поле"}},
    {_window, 0.5, 0.77, {"Big field", "Большое поле", "Großes Feld", "Вялікае поле"}},
    {_window, 0.5, 0.9, {"Huge field", "Огромное поле", "Riesiges Feld", "Вялікае поле"}},
},
closeButton{_window, 0.5, 0.8, {"Close", "Закрыть", "Schließen", "Зачыніць"}} {}

void StartFields::activate() {
    active = true;
}

bool StartFields::isActive() {
    return active;
}

const Field* StartFields::click(const Mouse _mouse) {
    if (active) {
        if (closeButton.in(_mouse)) {
            active = false;
            return nullptr;
        }
        for (int i=0; i < 4; ++i) {
            if (optionButton[i].in(_mouse)) {
                active = false;
                return startOptions + i;
            }
        }
    }
    return nullptr;
}

void StartFields::blit() const {
    if (active) {
        backplate.blit();
        for (int i=0; i < 4; ++i) {
            optionButton[i].blit();
        }
        closeButton.blit();
    }
}
