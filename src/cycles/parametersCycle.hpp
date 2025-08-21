/*
 * Copyright (C) 2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"


// Cycle for select variants to start
class ParametersCycle : public BaseCycle {
 private:
    GUI::HighlightedStaticText titleText;
    GUI::HighlightedStaticText widthText;
    GUI::TypeField<1> widthTypeField;
    GUI::HighlightedStaticText winWidthText;
    GUI::TypeField<1> winWidthTypeField;

    GUI::TextButton smallFieldButton;
    GUI::TextButton mediumFieldButton;
    GUI::TextButton bigFieldButton;
    GUI::TextButton hugeFieldButton;

    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputKeys(SDL_Keycode _key) override;
    void update() override;
    void inputText(const char* text) override;
    void draw() const override;

    // Shortcut functions
    void setParameter(int width, int winWidth);

 public:
    ParametersCycle(Window& window);
};
