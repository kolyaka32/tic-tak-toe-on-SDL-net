/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"
#include "serverGame.hpp"


bool ServerLobbyCycle::showAddress = false;

ServerLobbyCycle::ServerLobbyCycle()
: BaseCycle(),
titleText(0.5, 0.15, {"Wait for connection", "Ожидайте подключения", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 2, 28),
addressText(0.5, 0.3, {"Your address: %s", "Ваш адресс: %s", "Ihre Adresse: %s", "Ваш адрас: %s"}, 24),
copiedInfoBox(0.5, 0.37, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}, 24),
showAddressText(0.5, 0.45, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}, 24),
hideAddressText(0.5, 0.45, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}, 24) {
    // Resetting flag of showing address
    if (!isRestarted()) {
        showAddress = false;
        #if CHECK_ALL
        SDL_Log("Start server lobby");
        #endif
    }
    if (isAdditionalRestarted()) {
        stop();
        return;
    }

    // Getting string with full address of current app
    snprintf(currentAddress, sizeof(currentAddress), "%s:%u", server.getLocalIP(), server.getPort());

    // Setting showing/hidding address text
    if (showAddress) {
        addressText.setValues(currentAddress);
    } else {
        addressText.setValues("********");
    }
}

bool ServerLobbyCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    // Check on copying address
    if (addressText.in(mouse)) {
        // Copying address to buffer
        static char clipboardText[24];
        snprintf(clipboardText, sizeof(clipboardText), "%s", currentAddress);
        SDL_SetClipboardText(clipboardText);
        copiedInfoBox.reset();
        return true;
    }
    if (showAddress) {
        // Check on hiding address
        if (hideAddressText.in(mouse)) {
            showAddress = false;
            addressText.setValues("********");
            return true;
        }
    } else {
        // Check on showing address
        if (showAddressText.in(mouse)) {
            showAddress = true;
            addressText.setValues(currentAddress);
            return true;
        }
    }
    return false;
}

void ServerLobbyCycle::update() {
    BaseCycle::update();

    // Update infobox
    copiedInfoBox.update();

    // Getting internet packets
    switch (server.getCode()) {
    case ConnectionCode::Init:
        // Sending approving code
        server.connectToLastMessage();

        // Starting game (as server)
        runCycle<ServerGameCycle, Connection&>(server);
        // Exiting to menu after game
        stop();
        return;
    }
}

void ServerLobbyCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Draw main part
    titleText.blit();
    addressText.blit();
    copiedInfoBox.blit();

    if (showAddress) {
        hideAddressText.blit();
    } else {
        showAddressText.blit();
    }

    // Drawing buttons
    exitButton.blit();

    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}
