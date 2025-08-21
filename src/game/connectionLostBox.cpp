/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "connectionLostBox.hpp"
#include "../data/cycleTemplate.hpp"


bool ConnectionLostBox::active = false;

ConnectionLostBox::ConnectionLostBox(const Window& _window)
: mainText(_window, 0.5, 0.4, {"Connection lost", "Соединение потярено", "Verbindung verloren", "Злучэнне страчана"}, 2, 32),
reconnectButton(_window, 0.5, 0.5, {"Reconnect", "Переприсоединится", "Wiederverbinden", "Паўторна падлучыцца"}, 24),
closeButton(_window, 0.5, 0.6, {"Close", "Закрыть", "Schließen", "Зачыніць"}, 24),
background(_window, 0.5, 0.5, 0.82, 0.3, 20, 4) {}

int ConnectionLostBox::click(const Mouse _mouse) {
    if (active) {
        // Check, if return to menu
        if (closeButton.in(_mouse)) {
            CycleTemplate::stop();
            return 1;
        }
        // Check, if try to reconnect
        if (reconnectButton.in(_mouse)) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void ConnectionLostBox::blit() const {
    if (active) {
        background.blit();
        closeButton.blit();
        reconnectButton.blit();
        mainText.blit();
    }
}

void ConnectionLostBox::activate() {
    active = true;
}

void ConnectionLostBox::reset() {
    active = false;
}
