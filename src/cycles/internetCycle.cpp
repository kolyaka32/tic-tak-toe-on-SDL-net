/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <array>
#include "internetCycle.hpp"


InternetCycle::InternetCycle(Window& _window)
: GameCycle(_window),
playersTurnsTexts {
    {window, 0.5, 0.05, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}},
    {window, 0.5, 0.05, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}},
},
disconnectedBox(window, LanguagedText{"Connection lost", "Соединение потярено", "Verbindung verloren", "Злучэнне страчана"},
    std::array<GUI::TextButton, 2>{GUI::TextButton{window, 0.333, 0.6, {"Reconnect", "Переприсоединится", "Wiederverbinden", "Паўторна падлучыцца"}},
    GUI::TextButton{GUI::TextButton{window, 0.67, 0.5, {"Close", "Закрыть", "Schließen", "Зачыніць"}}}}),
termianatedBox(window, LanguagedText{"Connection terminated", "Соединение разорвано", "Verbindung unterbrochen", "Злучэнне разарвана"},
    std::array<GUI::TextButton, 1>{{GUI::TextButton{window, 0.5, 0.6, LanguagedText{"Close", "Закрыть", "Schließen", "Зачыніць"}}}}),
looseText(window, 0.5, 0.05, {"You loose", "Вы проиграли", "Sie haben verloren", "Вы прайгралі"}, 1),
winText(window, 0.5, 0.05, {"Win", "Победа", "Sieg", "Перамога"}, 1) {
    // Resetting flag
    if (!isRestarted()) {
        disconnectedBox.reset();
        termianatedBox.reset();
    }
    logAdditional("Start internet game cycle");
}

bool InternetCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (termianatedBox.click(mouse)) {
        return true;
    }
    if (disconnectedBox.click(mouse)) {
        return true;
    }
    return false;
}

void InternetCycle::update() {
    // Getting messages
    while (NET_Datagram* datagramm = internet.getNewMessages()) {
        GetPacket packet(datagramm);
        getInternetPacket(packet);
    }
    // Checking applied messages
    internet.checkResendMessages();

    // Appling status
    internet.checkNeedApplyConnection();

    // Checking status
    if (internet.checkStatus()) {
        disconnectedBox.activate();
    } else {
        disconnectedBox.reset();
    }
    // Basic update
    BaseCycle::update();
}

void InternetCycle::getInternetPacket(GetPacket& packet) {
    switch (ConnectionCode(packet.getData<Uint8>())) {
    case ConnectionCode::Quit:
        termianatedBox.activate();
        break;

    default:
        break;
    }
}
