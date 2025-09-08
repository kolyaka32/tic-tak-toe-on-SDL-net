/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "field.hpp"


// 
class WindowField : public GUI::Template, public Field {
 private:
    // Field window sizes
    static const float cellSide;   // Width and height of mine in pixels
    static const float separator;  // Width of separator between cells in pixels
    static const float upperLineHeight;  // Releative height of upper line for settings (add to main)

 public:
    WindowField(const Window& window);
    WindowField(const Field& field, const Window& window);

    // Drawing field with his background
    void blit() const;

    // Global options to work with field
    int getWidth() const;
    void setWidth(int width);
    int getWinWidth() const;
    void setWinWidth(int winWidth);
    int getWindowWidth() const;
    int getWindowHeight() const;
};
