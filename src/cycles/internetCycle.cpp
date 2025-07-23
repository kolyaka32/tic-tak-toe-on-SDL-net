/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


InternetCycle::InternetCycle(const App& _app)
: GameCycle(_app),
playersTurnsTexts {
    {_app.window, 0.5, 0.05, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}, 24, WHITE},
    {_app.window, 0.5, 0.05, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}, 24, WHITE},
},
disconnectedBox(_app.window),
termianatedBox(_app.window),
looseText(_app.window, 0.5, 0.35, {"You loose", "Вы проиграли", "Sie haben verloren", "Вы прайгралі"}, 30, WHITE),
winText(_app.window, 0.5, 0.35, {"Win", "Победа", "Sieg", "Перамога"}, 30, WHITE) {
    // Resetting flag
    if (!isRestarted()) {
        disconnectedBox.reset();
        termianatedBox.reset();
    }
}

bool InternetCycle::inputMouseDown(App& _app) {
    if (GameCycle::inputMouseDown(_app)) {
        return true;
    }
    if (termianatedBox.click(mouse)) {
        return true;
    }
    if (int code = disconnectedBox.click(mouse)) {
        // Check, if try to reconnect
        if (code == 2) {
            //connection;
        }
        return true;
    }
    return false;
}
