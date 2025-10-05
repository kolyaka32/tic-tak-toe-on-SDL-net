/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"
#include "serverGame.hpp"


bool ServerLobbyCycle::showAddress = false;

ServerLobbyCycle::ServerLobbyCycle(Window& _window)
: BaseCycle(_window),
titleText(window, 0.5, 0.15, {"Wait for connection", "Ожидайте подключения", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 2, Height::SubTitle),
addressText(window, 0.5, 0.3, {"Your address: %s", "Ваш адресс: %s", "Ihre Adresse: %s", "Ваш адрас: %s"}),
copiedInfoBox(window, 0.5, 0.4, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}),
showAddressText(window, 0.5, 0.5, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}),
hideAddressText(window, 0.5, 0.5, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}) {
    // Resetting flag of showing address
    if (!isRestarted()) {
        showAddress = false;
    }
    if (isAdditionalRestarted()) {
        stop();
        return;
    }

    // Getting string with full address of current app
    //snprintf(currentAddress, sizeof(currentAddress), "%s:%u", server.getLocalIP(), server.getPort());  // !

    // Setting showing/hidding address text
    if (showAddress) {
        addressText.setValues(currentAddress);
    } else {
        addressText.setValues("********");
    }
    logAdditional("Start server lobby cycle");
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
    /*switch (server.getCode()) {
    case ConnectionCode::Init:
        // Sending approving code
        server.connectToLastMessage();

        // Sending applying initialsiation message
        internet.sendAllConfirmed(ConnectionCode::Init);

        // Starting game (as server)
        runCycle<ServerGameCycle>(window);
        // Exiting to menu after game
        stop();
        return;

    default:
        break;
    }*/
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
