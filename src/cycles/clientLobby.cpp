/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientLobby.hpp"
#include "clientGame.hpp"


// Static objects for save inputted parameters
char ClientLobbyCycle::baseIP[15] = "127.0.0.1";
char ClientLobbyCycle::basePort[6] = "8000";

ClientLobbyCycle::ClientLobbyCycle(Window& _window)
: BaseCycle(_window),
enterIPText(window, 0.5, 0.2, {"Enter IP:", "Введите IP:", "Geben Sie die IP ein:", "Увядзіце IP:"}, Height::SubTitle),
enterIPField(window, 0.5, 0.32, baseIP),
enterPortText(window, 0.5, 0.45, {"Enter port:", "Введите порт:", "Port eingeben:", "Увядзіце порт:"}, Height::SubTitle),
enterPortField(window, 0.5, 0.57, basePort),
pasteButton(window, 0.5, 0.75, {"Paste the address", "Вставить адрес", "Kopierte Adresse", "Уставіць адрас"}),
connectButton(window, 0.5, 0.9, {"Connect", "Присоединится", "Beitritt", "Далучыцца"}) {
    // Starting random getting socket
    internet.openClient();

    // Stopping, if go from another cycle
    if (isAdditionalRestarted()) {
        stop();
        return;
    }

    logAdditional("Start client lobby cycle");
}

ClientLobbyCycle::~ClientLobbyCycle() {
    internet.close();
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
                logAdditional("Couldn't connect - wrong port");
                return true;
            }
        }
        // Saving inputted address
        memcpy(baseIP, enterIPField.getString(), sizeof(baseIP));
        memcpy(basePort, portTextCorrected, sizeof(basePort));
        // Trying connect at specified address
        internet.sendFirst(StringDestination(enterIPField.getString(), std::stoi(portTextCorrected)), ConnectionCode::Init, 1);
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
    while (auto message = internet.getNewMessages()) {
        switch (ConnectionCode(message->buf[0])) {
        case ConnectionCode::Init:
            // Settings options to this connection
            internet.connectTo(message->addr, message->port);
            // Starting game
            runCycle<ClientGameCycle>(window);
            // Exiting to menu after game
            stop();
            return;

        default:
            return;
        }
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
        logAdditional("Couldn't get clipboard");
        return;
    }
    // Find IP text (first part)
    int i = 0;
    for (; clipboard[i]; ++i) {
        // Finding : as port separator
        if (clipboard[i] == ':') {
            break;
        }
        // Checking coorection of string
        if (clipboard[i] != '.' && (clipboard[i] < '0' || clipboard[i] > '9')) {
            logAdditional("Wrong clipboard: %s", clipboard);
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
    logAdditional("From clipboard: IP: %s, port: %s", clipboard, clipboard+i);
    enterIPField.setString(clipboard);
    enterPortField.setString(clipboard+i);
    SDL_free(clipboard);
}

void ClientLobbyCycle::writeBaseIP(const char* _text) {
    snprintf(baseIP, sizeof(baseIP), "%s", _text);
}

const char* ClientLobbyCycle::getBaseIP() {
    return baseIP;
}

void ClientLobbyCycle::writeBasePort(const char* _text) {
    snprintf(basePort, sizeof(basePort), "%s", _text);
}

const char* ClientLobbyCycle::getBasePort() {
    return basePort;
}
