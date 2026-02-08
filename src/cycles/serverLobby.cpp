/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"
#include "serverGame.hpp"


bool ServerLobbyCycle::showAddress = false;

ServerLobbyCycle::ServerLobbyCycle(Window& _window)
: BaseCycle(_window),
titleText(window, 0.5, 0.15,
    {"Wait for connection", "Ожидайте подключения", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 2, Height::SubTitle),
hideAddressText(window, 0.5, 0.3,
    {"Your address: **************", "Ваш адресс: **************", "Ihre Adresse: **************", "Ваш адрас: **************"}),
showAddressText(window, 0.5, 0.3,
    {"Your address: %s:%d", "Ваш адресс: %s:%d", "Ihre Adresse: %s:%d", "Ваш адрас: %s:%d"}),
copiedInfoBox(window, 0.5, 0.4, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}),
showAddressButton(window, 0.5, 0.5, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}),
hideAddressButton(window, 0.5, 0.5, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}) {
    // Getting string with full address of current app
    showAddressText.setValues(internet.getHostName(), internet.getPort());

    // Resetting flag of showing address
    if (!isRestarted()) {
        showAddress = false;
    }
    logAdditional("Start server lobby cycle");
}

bool ServerLobbyCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    // Check on copying address
    if (hideAddressText.in(mouse)) {
        // Copying address to buffer
        static char clipboardText[24];
        snprintf(clipboardText, sizeof(clipboardText), "%s:%d", internet.getHostName(), internet.getPort());
        SDL_SetClipboardText(clipboardText);
        copiedInfoBox.reset();
        return true;
    }
    if (showAddress) {
        // Check on hiding address
        if (hideAddressButton.in(mouse)) {
            showAddress = false;
            return true;
        }
    } else {
        // Check on showing address
        if (showAddressButton.in(mouse)) {
            showAddress = true;
            return true;
        }
    }
    return false;
}

void ServerLobbyCycle::update() {
    BaseCycle::update();

    // Update infobox
    copiedInfoBox.update();

    // Getting internet data (applied messages)
    while (const GetPacket* packet = internet.getNewMessages()) {
        switch (ConnectionCode(packet->getData<Uint8>(0))) {
        case ConnectionCode::Init:
            // Connecting to getted address
            internet.connectTo(Destination{packet->getSourceAddress()});

            // Sending applying initialsiation message
            internet.sendAllConfirmed(ConnectionCode::Init);

            // Starting game (as server)
            App::setNextCycle(Cycle::ServerGame);
            return;

        default:
            return;
        }
    }
}

void ServerLobbyCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Draw main part
    titleText.blit();
    copiedInfoBox.blit();

    if (showAddress) {
        showAddressText.blit();
        showAddressButton.blit();
    } else {
        hideAddressText.blit();
        hideAddressButton.blit();
    }

    // Drawing buttons
    exitButton.blit();

    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}
