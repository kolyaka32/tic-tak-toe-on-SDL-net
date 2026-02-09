/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientLobby.hpp"
#include "clientGame.hpp"


ClientLobbyCycle::ClientLobbyCycle(Window& _window)
: BaseCycle(_window),
serverScroller(_window, 0.5, 0.5, 1.0, 0.9, 6, {"No servers found", "Сервера не найдены", "Kein Server gefunden", "Сервера не знойдзены"}),
targetConnectButton(_window, 0.5, 0.9, {"Connect by IP", "Присоединиться по IP", "Über IP beitreten", "Далучыцца па IP"}),
targetConnectMenu(_window) {
    // Starting random getting socket
    logAdditional("Start client lobby cycle");

    if (!isRestarted()) {
        targetConnectMenu.reset();
    }
}

bool ClientLobbyCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    if (targetConnectMenu.click(mouse)) {
        return true;
    }
    if (targetConnectButton.in(mouse)) {
        targetConnectMenu.activate();
        return true;
    }
    return false;
}

void ClientLobbyCycle::inputMouseUp() {
    settings.unClick();
    targetConnectMenu.unclick();
}

void ClientLobbyCycle::inputKeys(SDL_Keycode _key) {
    targetConnectMenu.press(_key);
}

void ClientLobbyCycle::update() {
    BaseCycle::update();
    targetConnectMenu.update();

    // Getting internet data
    while (const GetPacket* packet = internet.getNewMessages()) {
        switch (ConnectionCode(packet->getData<Uint8>(0))) {
        case ConnectionCode::Init:
            // Connecting to getted address
            internet.connectTo(Destination{packet->getSourceAddress()});

            // Starting game (as client)
            App::setNextCycle(Cycle::ClientGame);
            return;

        default:
            return;
        }
    }
}

void ClientLobbyCycle::inputText(const char* _text) {
    targetConnectMenu.write(_text);
}

void ClientLobbyCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Drawing buttons
    exitButton.blit();

    // Draw main part
    serverScroller.blit();
    targetConnectButton.blit();
    targetConnectMenu.blit();

    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}
