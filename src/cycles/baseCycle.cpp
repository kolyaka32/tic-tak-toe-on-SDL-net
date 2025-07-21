/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Base cycle class
BaseCycle::BaseCycle(const App& _app)
: exitButton(_app.window, 0.05, 0.05, IMG_GUI_QUIT_BUTTON),
settings(_app) {}

bool BaseCycle::inputMouseDown(App& _app) {
    if (settings.click(mouse, _app)) {
        return true;
    }
    if (exitButton.in(mouse)) {
        stop();
        return true;
    }
    return false;
}

void BaseCycle::update(App& _app) {
    settings.update(_app);
}

void BaseCycle::inputMouseUp(App& _app) {
    settings.unClick();
}

void BaseCycle::inputMouseWheel(App& _app, float _wheelY) {
    settings.scroll(_app, mouse, _wheelY);
}
