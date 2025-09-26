/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


InternetCycle::InternetCycle(Window& _window)
: GameCycle(_window),
playersTurnsTexts {
    {window, 0.5, 0.05, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}},
    {window, 0.5, 0.05, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}},
},
disconnectedBox(window),
termianatedBox(window),
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
