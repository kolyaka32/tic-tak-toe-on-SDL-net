/*
 * Copyright (C) 2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "parametersCycle.hpp"
#include "../game/gameField.hpp"


ParametersCycle::ParametersCycle()
: titleText(0.5, 0.1, {"Select field", "Выберете поле", "Feld auswählen", "Выберыце поле"}, 3, 40),
widthText(0.05, 0.25, {"Field width:", "Ширина поля:", "Feldbreite:", "Шырыня поля:"}, 2, 24,
    WHITE, GUI::Aligment::Left),
widthTypeField(0.8, 0.25, 20, std::to_string(GameField::getWidth()).c_str()),
winWidthText(0.05, 0.38, {"Win width:", "Победная длинна:", "Gewinnbreite:", "Выйгрышная шырыня:"}, 2, 24,
    WHITE, GUI::Aligment::Left),
winWidthTypeField(0.8, 0.38, 20, std::to_string(GameField::getWinWidth()).c_str()),
smallFieldButton(0.5, 0.51, {"Small field", "Маленькое поле", "Kleines Feld", "Невялікае поле"}, 24),
mediumFieldButton(0.5, 0.64, {"Medium field", "Среднее поле", "Mittleres Feld", "Сярэдняе поле"}, 24),
bigFieldButton(0.5, 0.77, {"Big field", "Большое поле", "Großes Feld", "Вялікае поле"}, 24),
hugeFieldButton(0.5, 0.9, {"Huge field", "Огромное поле", "Riesiges Feld", "Вялікае поле"}, 24) {
    #if CHECK_ALL
    SDL_Log("Start parameters selection cycle");
    #endif
}

bool ParametersCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    // Connection part
    if (widthTypeField.click(mouse)) {
        // Checking correction of text
        int newWidth = *widthTypeField.getString() - '0';
        // Changing size
        GameField::setWidth(newWidth);
        // Changing window size
        window.setWidth(GameField::getWindowWidth());
        window.setHeight(GameField::getWindowHeight());
        // Restarting cycle
        restart();
        #if CHECK_ALL
        SDL_Log("Setting game field width to %u", GameField::getWidth());
        #endif
        return true;
    }
    if (winWidthTypeField.click(mouse)) {
        // Checking correction of text
        int newWinWidth = *winWidthTypeField.getString() - '0';
        // Changing size
        GameField::setWinWidth(newWinWidth);
        // Changing text (for correction)
        winWidthTypeField.setString(std::to_string(GameField::getWinWidth()).c_str());
        #if CHECK_ALL
        SDL_Log("Setting game field win width to %u", GameField::getWinWidth());
        #endif
        return true;
    }
    if (smallFieldButton.in(mouse)) {
        setParameter(3, 3);
        return true;
    }
    if (mediumFieldButton.in(mouse)) {
        setParameter(5, 4);
        return true;
    }
    if (bigFieldButton.in(mouse)) {
        setParameter(7, 5);
        return true;
    }
    if (hugeFieldButton.in(mouse)) {
        setParameter(9, 6);
        return true;
    }
    return false;
}

void ParametersCycle::inputMouseUp() {
    settings.unClick();
    widthTypeField.unclick();
    winWidthTypeField.unclick();
}

void ParametersCycle::inputKeys(SDL_Keycode _key) {
    widthTypeField.type(_key);
    winWidthTypeField.type(_key);
}

void ParametersCycle::update() {
    BaseCycle::update();

    // Updating typeboxes
    mouse.updatePos();
    widthTypeField.update(mouse.getX());
    winWidthTypeField.update(mouse.getX());
}

void ParametersCycle::inputText(const char* text) {
    // Inputing text
    widthTypeField.writeString(text);
    winWidthTypeField.writeString(text);
}

void ParametersCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Main part
    titleText.blit();
    widthText.blit();
    widthTypeField.blit();
    winWidthText.blit();
    winWidthTypeField.blit();
    smallFieldButton.blit();
    mediumFieldButton.blit();
    bigFieldButton.blit();
    hugeFieldButton.blit();

    // System part
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}

void ParametersCycle::setParameter(int _width, int _winWidth) {
    // Changing parameters of field
    GameField::setWidth(_width);
    GameField::setWinWidth(_winWidth);
    // Changing window size
    window.setWidth(GameField::getWindowWidth());
    window.setHeight(GameField::getWindowHeight());
    // Restarting cycle
    restart();
    #if CHECK_ALL
    SDL_Log("Setting game field width to %u, win width to %u", _width, _winWidth);
    #endif
}
