/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Scary image, that show with small chanse at screen
class Screamer {
private:
    GUI::TextButton acceptButton;
    bool active = false;

public:
    Screamer();
    bool click(const Mouse mouse);
    void update();
    void blit() const;
};
