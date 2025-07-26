/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"


GameField::GameField()
: Field() {}

GameField::~GameField() {
    Field::~Field();
}

void GameField::setTextureOffset(int _state) {
    offset = _state;
}

int GameField::getXPos(const Mouse _mouse) {
    return _mouse.getX() / (CELL_SIDE + SEPARATOR);
}

int GameField::getYPos(const Mouse _mouse) {
    return (_mouse.getY() - UPPER_LINE) / (CELL_SIDE + SEPARATOR);
}

void GameField::clickSingle(const Mouse _mouse) {
    if (_mouse.getY() > UPPER_LINE) {
        Field::clickSingle(getXPos(_mouse), getYPos(_mouse));
    }
}

void GameField::clickTwo(const Mouse _mouse) {
    if (_mouse.getY() > UPPER_LINE) {
        Field::clickTwo(getXPos(_mouse), getYPos(_mouse));
        // Changing active player, if in game
        if (getState() <= GameState::OpponentPlay) {
            // Inversing color of active player
            offset ^= 1;
        }
    }
}

bool GameField::clickMultiplayerCurrent(const Mouse _mouse) {
    if (_mouse.getY() > UPPER_LINE) {
        return Field::clickMultiplayerCurrent(getXPos(_mouse), getYPos(_mouse));
    }
    return false;
}

void GameField::blit(const Window& _target) const {
    // Rendering cells with their background
    for (int y=0; y < width; ++y) {
        for (int x=0; x < width; ++x) {
            const SDL_FRect dest = {float(x * (CELL_SIDE + SEPARATOR)), float(y * (CELL_SIDE + SEPARATOR) + UPPER_LINE), CELL_SIDE, CELL_SIDE};
            // Rendering background
            _target.blit(IMG_CELL, dest);

            // Rendering cells
            switch (getCell(x, y)) {
            case Cell::Current:
                _target.blit(IMG_names(IMG_GREEN_CROSS + offset), dest);
                break;

            case Cell::Opponent:
                _target.blit(IMG_names(IMG_RED_CIRCLE - offset), dest);
                break;
            }
        }
    }
}
