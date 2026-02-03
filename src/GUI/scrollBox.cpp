/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::ScrollBox(const Window& _window, float _posX, float _posY, float _width, float _height,
    std::vector<SourceItem> _startItems, const LanguagedText _emptyItemsText, int _maxItems)
: Template(_window),
maxItems(_maxItems),
backplate(_window, _posX, _posY, _width, _height, 20.0, 4.0),
emptySavesText(_window, _posX, _posY - _height/2, _emptyItemsText, 1) {
    // Creating options to start
    for (int i=0; i < _startItems.size(); ++i) {
        items.push_back(new Item(_window, _startItems[i], _startItems.size() - i - 1));
    }
}

template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::~ScrollBox() {
    for (int i=0; i < items.size(); ++i) {
        delete items[i];
    }
}

template <class Item, class SourceItem>
const Item* GUI::ScrollBox<Item, SourceItem>::click(const Mouse _mouse) {
    for (int i=startField; i < endField; ++i) {
        if (items[i]->in(_mouse)) {
            return &items[i];
        }
    }
    return nullptr;
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::scroll(float _wheelY) {
    Mouse mouse{};
    mouse.updatePos();
    // Check, if scroll in this menu
    if (backplate.in(mouse)) {
        if (_wheelY > 0) {
            for (;_wheelY > 0; --_wheelY) {
                // Check, if can scroll up
                if (endField < items.size()) {
                    startField++;
                    endField++;
                    for (int i=0; i < items.size(); ++i) {
                        items[i]->moveDown();
                    }
                } else {
                    return;
                }
            }
        } else {
            for (;_wheelY < 0; ++_wheelY) {
                // Check, if can scroll down
                if (startField > 0) {
                    startField--;
                    endField--;
                    for (int i=0; i < items.size(); ++i) {
                        items[i]->moveUp();
                    }
                } else {
                    return;
                }
            }
        }
    }
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::blit() const {
    backplate.blit();
    // Check, if has fields
    if (endField) {
        for (int i=startField; i < endField; ++i) {
            items[i]->blit();
        }
    } else {
        emptySavesText.blit();
    }
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::addItem(const SourceItem& _sourceItem) {
    // Check, if add, when has place
    if (endField < maxItems) {
        // Moving all infos
        for (int i=0; i < items.size(); ++i) {
            items[i]->moveDown();
        }
        // Creating new
        items.push_back(new Item(window, _sourceItem, 0));
        endField++;
        return;
    }
    // Check, if need to save current position in list
    if (endField == items.size()) {
        // Moving all down
        for (int i=0; i < items.size(); ++i) {
            items[i]->moveDown();
        }
        // Creating new
        items.push_back(new Item(window, _sourceItem, 0));
        endField++;
        startField++;
        return;
    } else {
        // Placing and not showing
        items.push_back(new Item(window, _sourceItem, startField - endField));
    }
}
