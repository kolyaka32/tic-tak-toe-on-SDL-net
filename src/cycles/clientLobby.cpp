/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "clientLobby.hpp"
#include "clientGame.hpp"


// Base link connections realisations
char baseIP[12] = "127.0.0.1";
char basePort[6] = "8000";


ClientLobbyCycle::ClientLobbyCycle(App& _app)
: BaseCycle(_app),
enterIPText(_app.window, 0.5, 0.2, {"Enter IP:", "Введите IP:", "-", "Увядзіце IP:"}, 30, WHITE),
enterIPField(_app.window, 0.5, 0.32, 20, baseIP),
enterPortText(_app.window, 0.5, 0.5, {"Enter port:", "Введите порт:", "Port eingeben:", "Увядзіце порт:"}, 30, WHITE),
enterPortField(_app.window, 0.5, 0.62, 20, basePort),
connectButton(_app.window, 0.5, 0.78, {"Connect", "Присоединится", "Beitritt", "Далучыцца"}, 22, WHITE),
pasteButton(_app.window, 0.5, 0.9, {"Paste the address", "Вставить адрес", "Kopierte Adresse", "Уставіць адрас"}, 22, WHITE) {
    if (isAdditionalRestarted()) {
        stop();
        return;
    }
}

bool ClientLobbyCycle::inputMouseDown(App& _app) {
    if (BaseCycle::inputMouseDown(_app)) {
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

void ClientLobbyCycle::inputMouseUp(App& app) {
    settings.unClick();
    enterIPField.unclick();
    enterPortField.unclick(); 
}

void ClientLobbyCycle::inputKeys(App& app, SDL_Keycode key) {
    enterIPField.type(key);
    enterPortField.type(key);
}

void ClientLobbyCycle::update(App& _app) {
    BaseCycle::update(_app);

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
        Field::setWidth(client.lastPacket->getData<Uint8>(2));
        Field::setWinWidth(client.lastPacket->getData<Uint8>(3));
        // Changing window size
        _app.window.setWidth(Field::getWindowWidth());
        _app.window.setHeight(Field::getWindowHeight());
        // Starting game
        runCycle<ClientGameCycle, Connection&>(_app, client);
        // Exiting to menu after game
        stop();
        return;
    }
}

void ClientLobbyCycle::inputText(App& app, const char* text) {
    // Inputing text
    enterIPField.writeString(text);
    enterPortField.writeString(text);
}

void ClientLobbyCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Drawing buttons
    exitButton.blit(_app.window);

    // Draw main part
    enterIPText.blit(_app.window);
    enterPortText.blit(_app.window);
    pasteButton.blit(_app.window);
    connectButton.blit(_app.window);
    enterIPField.blit();
    enterPortField.blit();

    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
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
