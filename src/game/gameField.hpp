/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "field.hpp"


// Cycle with field with game objects on it
class GameField : public GUI::Template {
 private:
    // Game field
    static Field currentField;
    // Function for do after game end
    void checkEnd();
    // Similar to checkEnd(), but for client side
    void checkEndInverted();

 public:
    explicit GameField(const Window& window);
    GameState getState() const;
    void setState(GameState state);
    static int getWidth();
    static int getWindowWidth();
    static int getWindowHeight();

    bool isGameEnd() const;
    void restart();
    void setNewField(const Field* field, Window& window);  // Return true, if need to restart cycle
    const Field& saveField();
    const Array<char> getSave() const;

    void blit() const override;

    // Game turns
    void tryClickSingle(const Mouse mouse);         // Clicking in singleplayer mode, return if have turn
    void tryClickCoop(const Mouse mouse);           // Clicking in coop mode, return if have turn
    bool tryClickServerCurrent(const Mouse mouse);  // Clicking on server side by current user, return if have turn
    bool tryClickClientCurrent(const Mouse mouse);  // Clicking on client side by current user, return if have turn
    Uint8 getLastTurn(const Mouse mouse);           // Return last turn
    void clickServerOpponent(Uint8 position);       // Clicking on server side by internet connection
    void clickClientOpponent(Uint8 position);       // Clicking on client side by internet connection
};
