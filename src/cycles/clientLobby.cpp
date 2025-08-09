/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientLobby.hpp"
#include "clientGame.hpp"


// Base link connections realisations
char baseIP[12] = "127.0.0.1";
char basePort[6] = "8000";


ClientLobbyCycle::ClientLobbyCycle()
: BaseCycle(),
enterIPText(0.5, 0.2, {"Enter IP:", "Введите IP:", "-", "Увядзіце IP:"}, 30, WHITE),
enterIPField(0.5, 0.32, 20, baseIP),
enterPortText(0.5, 0.5, {"Enter port:", "Введите порт:", "Port eingeben:", "Увядзіце порт:"}, 30, WHITE),
enterPortField(0.5, 0.62, 20, basePort),
pasteButton(0.5, 0.75, {"Paste the address", "Вставить адрес", "Kopierte Adresse", "Уставіць адрас"}, 24, WHITE),
connectButton(0.5, 0.9, {"Connect", "Присоединится", "Beitritt", "Далучыцца"}, 24, WHITE) {
    if (isAdditionalRestarted()) {
        stop();
        return;
    }
}

bool ClientLobbyCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }

    // Connection part
    if (enterIPField.click(mouse)) {
        return true;
    }
    if (enterPortField.click(mouse)) {
        return true;
    }

    // Check, if press paste data
    if (pasteButton.in(mouse)) {
        pasteFromClipboard();
        return true;
    }

    // Trying to connect at specified address
    if (connectButton.in(mouse)) {
        // Checking correction of port text
        char portTextCorrected[7];
        memcpy(portTextCorrected, enterPortField.getString(), 7);
        for (char* c = portTextCorrected; *c; ++c) {
            if (*c < '0' || *c > '9') {
                #if CHECK_ALL
                SDL_Log("Couldn't connect - wrong port");
                #endif
                return true;
            }
        }
        // Trying connect at specified address
        client.tryConnect(enterIPField.getString(), std::stoi(portTextCorrected));
        return true;
    }
    return false;
}

void ClientLobbyCycle::inputMouseUp() {
    settings.unClick();
    enterIPField.unclick();
    enterPortField.unclick(); 
}

void ClientLobbyCycle::inputKeys(SDL_Keycode _key) {
    enterIPField.type(_key);
    enterPortField.type(_key);
}

void ClientLobbyCycle::update() {
    BaseCycle::update();

    // Updating typeboxes
    mouse.updatePos();
    enterIPField.update(mouse.getX());
    enterPortField.update(mouse.getX());

    // Getting internet data
    switch (client.getCode()) {
    case ConnectionCode::Init:
        // Settings options to this connection
        client.connectToLastMessage();
        // Applying field size
        GameField::setWidth(client.lastPacket->getData<Uint8>(2));
        GameField::setWinWidth(client.lastPacket->getData<Uint8>(3));
        // Changing window size
        window.setWidth(GameField::getWindowWidth());
        window.setHeight(GameField::getWindowHeight());
        // Starting game
        runCycle<ClientGameCycle, Connection&>(client);
        // Exiting to menu after game
        stop();
        return;
    }
}

void ClientLobbyCycle::inputText(const char* text) {
    // Inputing text
    enterIPField.writeString(text);
    enterPortField.writeString(text);
}

void ClientLobbyCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Drawing buttons
    exitButton.blit();

    // Draw main part
    enterIPText.blit();
    enterPortText.blit();
    pasteButton.blit();
    connectButton.blit();
    enterIPField.blit();
    enterPortField.blit();

    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}

void ClientLobbyCycle::pasteFromClipboard() {
    // Getting data from clipboard
    char* clipboard = SDL_GetClipboardText();

    // Check text on correction
    if (clipboard == nullptr) {
        #if CHECK_ALL
        SDL_Log("Couldn't get clipboard");
        #endif
        return;
    }
    // Find IP text (first part)
    int i=0;
    for (; clipboard[i]; ++i) {
        // Finding : as port separator
        if (clipboard[i] == ':') {
            break;
        }
        // Checking coorection of string
        if (clipboard[i] != '.' && (clipboard[i] < '0' || clipboard[i] > '9')) {
            #if CHECK_ALL
            SDL_Log("Wrong clipboard: %s", clipboard);
            #endif
            SDL_free(clipboard);
            return;
        }
    }
    clipboard[i] = '\0';
    i++;
    // Finding end of port text
    for (int k=i; clipboard[k]; ++k) {
        if (clipboard[k] < '0' || clipboard[k] > '9') {
            clipboard[k] = '\0';
            break;
        }
    }
    #if CHECK_ALL
    SDL_Log("From clipboard: IP: %s, port: %s", clipboard, clipboard+i);
    #endif
    enterIPField.setString(clipboard);
    enterPortField.setString(clipboard+i);
    SDL_free(clipboard);
}
