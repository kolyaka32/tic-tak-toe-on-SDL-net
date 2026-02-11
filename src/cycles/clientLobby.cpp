/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientLobby.hpp"
#include "clientGame.hpp"


ClientLobbyCycle::ClientLobbyCycle(Window& _window)
: BaseCycle(_window),
broadcastSendSocket(),
serverScroller(_window, 0.5, 0.45, 1.0, 0.7, 5,
    {"No servers found", "Сервера не найдены", "Kein Server gefunden", "Сервера не знойдзены"}),
updateButton(_window, 0.5, 0.85, {"Update", "Обновить", "Update", "Абнаўленне"}),
targetConnectButton(_window, 0.5, 0.95,
    {"Connect by IP", "Присоединиться по IP", "Über IP beitreten", "Далучыцца па IP"}),
targetConnectMenu(_window) {
    // Starting random getting socket
    logAdditional("Start client lobby cycle");

    // Setting to correct send broadcast
    broadcastSendSocket.setSendBroadcast();

    // First auto searching
    updateList();

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
    if (updateButton.in(mouse)) {
        updateList();
        return true;
    }
    if (targetConnectButton.in(mouse)) {
        targetConnectMenu.activate();
        return true;
    }
    if (int i = serverScroller.click(mouse)) {
        // Connecting to selected server
        internet.sendFirst(serverDatas[i].getAddress(), {ConnectionCode::Init, 1});
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

    // Getting internet data from general socket
    while (const GetPacket* packet = internet.getNewMessages()) {
        switch (ConnectionCode(packet->getData<Uint8>(0))) {
        case ConnectionCode::Init:
            // Connecting to getted address
            internet.connectTo(Destination{packet->getSourceAddress()});

            // Starting game (as client)
            App::setNextCycle(Cycle::ClientGame);
            break;

        default:
            break;
        }
    }

    // Getting data from broadcast socket
    // Getting internet data
    while (const GetPacket* packet = broadcastSendSocket.recieve()) {
        if (packet->isBytesAvaliable(2)) {
            switch (ConnectionCode(packet->getData<Uint8>(0))) {
            case ConnectionCode::Server:
                // Get server information
                // Adding to list
                serverDatas.emplace_back(packet->getSourceAddress(), int(getTime()-startSearchTimer));
                // Adding variant to select menu
                serverScroller.addItem(serverDatas[serverDatas.size()-1]);
                break;

            default:
                return;
            }
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
    updateButton.blit();
    targetConnectButton.blit();
    // Drawing target connect menu above all
    targetConnectMenu.blit();

    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}

void ClientLobbyCycle::updateList() {
    // Clearing previous data
    serverScroller.clear();
    serverDatas.clear();
    // Sending searching message to broadcast
    Destination dest{"255.255.255.255", BROADCAST_PORT};
    broadcastSendSocket.send(dest, {ConnectionCode::Search, 1});
    // Update timer
    startSearchTimer = getTime();
}
