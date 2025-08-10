/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "terminatedBox.hpp"
#include "../data/cycleTemplate.hpp"


bool TerminatedBox::active = false;

TerminatedBox::TerminatedBox()
: mainText(0.5, 0.45, {"Connection terminated", "Соединение разорвано", "Verbindung unterbrochen", "Злучэнне разарвана"}, 1, 32, WHITE),
closeButton(0.5, 0.55, {"Close", "Закрыть", "Schließen", "Зачыніць"}, 24, WHITE),
background(0.5, 0.5, 0.82, 0.2, 20, 4) {}

bool TerminatedBox::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        if (closeButton.in(_mouse)) {
            CycleTemplate::stop();
        }
        // Blocking other actions, while box open
        return true;
    }
    return false;
}

void TerminatedBox::activate() {
    active = true;
}

void TerminatedBox::reset() {
    active = false;
}

bool TerminatedBox::isActive() {
    return active;
}

void TerminatedBox::blit() const {
    if (active) {
        background.blit();
        closeButton.blit();
        mainText.blit();
    }
}
