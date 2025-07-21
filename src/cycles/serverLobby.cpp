/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"
#include "selectCycle.hpp"
#include "serverGame.hpp"


bool ServerLobbyCycle::showAddress = false;

ServerLobbyCycle::ServerLobbyCycle(App& _app)
: BaseCycle(_app),
titleText(_app.window, 0.5, 0.15, {"Wait for connection", "Ожидайте подключения", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 30, WHITE),
addressText(_app.window, 0.5, 0.3, {"Your address: %s", "Ваш адресс: %s", "Ihre Adresse: %s", "Ваш адрас: %s"}, 22, WHITE),
copiedInfoBox(_app.window, 0.5, 0.37, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}, 22, WHITE),
showAddressText(_app.window, 0.5, 0.45, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}, 22),
hideAddressText(_app.window, 0.5, 0.45, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}, 22) {
    // Resetting flag of showing address
    if (!isRestarted()) {
        showAddress = false;
    }
    if (isAdditionalRestarted()) {
        stop();
        return;
    }

    // Getting string with full address of current app
    sprintf(currentAddress, "%s:%u", server.getLocalIP(), server.getPort());

    // Setting showing/hidding address text
    if (showAddress) {
        addressText.setValues(_app.window, currentAddress);
    } else {
        addressText.setValues(_app.window, "********");
    }
}

bool ServerLobbyCycle::inputMouseDown(App& _app) {
    if (BaseCycle::inputMouseDown(_app)) {
        return true;
    }
    // Check on copying address
    if (addressText.in(mouse)) {
        // Copying address to buffer
        static char clipboardText[20];
        strcpy(clipboardText, currentAddress);
        SDL_SetClipboardText(clipboardText);
        copiedInfoBox.reset();
        return true;
    }
    if (showAddress) {
        // Check on hiding address
        if (hideAddressText.in(mouse)) {
            showAddress = false;
            addressText.setValues(_app.window, "********");
            return true;
        }
    } else {
        // Check on showing address
        if (showAddressText.in(mouse)) {
            showAddress = true;
            addressText.setValues(_app.window, currentAddress);
            return true;
        }
    }
    return false;
}

void ServerLobbyCycle::update(App& _app) {
    BaseCycle::update(_app);

    // Update infobox
    copiedInfoBox.update();

    // Getting internet packets
    switch (server.getCode()) {
    case ConnectionCode::Init:
        // Sending approving code
        server.connectToLastMessage();

        // Starting game (as server)
        runCycle<ServerGameCycle, Connection&>(_app, server);
        // Exiting to menu after game
        stop();
        return;
    }
}

void ServerLobbyCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Draw main part
    titleText.blit(_app.window);
    addressText.blit(_app.window);
    copiedInfoBox.blit(_app.window);

    if (showAddress) {
        hideAddressText.blit(_app.window);
    } else {
        showAddressText.blit(_app.window);
    }

    // Drawing buttons
    exitButton.blit(_app.window);

    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
