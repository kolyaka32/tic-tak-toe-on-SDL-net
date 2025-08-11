/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


InternetCycle::InternetCycle()
: GameCycle(),
playersTurnsTexts {
    {0.5, 0.05, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}, 24, WHITE},
    {0.5, 0.05, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}, 24, WHITE},
},
disconnectedBox(),
termianatedBox(),
looseText(0.5, 0.35, {"You loose", "Вы проиграли", "Sie haben verloren", "Вы прайгралі"}, 1, 32, WHITE),
winText(0.5, 0.35, {"Win", "Победа", "Sieg", "Перамога"}, 1, 32, WHITE) {
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
