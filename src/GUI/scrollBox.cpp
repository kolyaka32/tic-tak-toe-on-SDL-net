/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::ScrollBox(const Window& _window, float _posX, float _posY, float _width, float _height,
    std::vector<SourceItem> _startItems, const LanguagedText&& _emptyItemsText, int _maxItems)
: Template(_window),
backplate(_window, _posX, _posY, _width, _height, 20.0, 4.0),
#if (USE_SDL_FONT) && (PRELOAD_FONTS)
emptySavesText(_window, _posX, _posY - _height/4, std::move(_emptyItemsText), 1),
#endif
maxItems(_maxItems) {
    // Creating options to start
    for (int i=0; i < items.size(); ++i) {
        items.emplace_back(_window, _startItems[i], _startItems.size() - i - 2);
        logAdditional("Object placed");
    }
    startField = 0;
    endField = min((int)items.size(), maxItems);
    logAdditional("Created scrolling box, start %d, end %d, size %d", startField, endField, items.size());
}

template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::ScrollBox(ScrollBox&& _object) noexcept 
: Template(_object.window),
startField(_object.startField),
endField(_object.endField),
maxItems(_object.maxItems),
#if (USE_SDL_FONT) && (PRELOAD_FONTS)
emptySavesText(std::move(_object.emptySavesText)),
#endif
backplate(std::move(_object.backplate)) {}

template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::~ScrollBox() noexcept {
    items.clear();
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::addItem(const SourceItem& _sourceItem) {
    // Check, if add, when has place
    if (endField < maxItems) {
        // Moving all infos
        for (int i=0; i < items.size(); ++i) {
            items[i].moveDown();
        }
        items.emplace_back(window, _sourceItem, 0);
        endField++;
        return;
    }
    // Check, if need to save current position in list
    if (endField == items.size()) {
        // Moving all down
        for (int i=0; i < items.size(); ++i) {
            items[i].moveDown();
        }
        items.emplace_back(window, _sourceItem, 0);
        endField++;
        startField++;
        return;
    }
    // Placing and not showing
    items.emplace_back(window, _sourceItem, startField - endField);
}

template <class Item, class SourceItem>
int GUI::ScrollBox<Item, SourceItem>::click(const Mouse _mouse) const {
    for (int i=startField; i < endField; ++i) {
        if (items[i].in(_mouse)) {
            return i+1;
        }
    }
    return 0;
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
                        items[i].moveDown();
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
                        items[i].moveUp();
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
            items[i].blit();
        }
    } else {
        #if (USE_SDL_FONT) && (PRELOAD_FONTS)
        emptySavesText.blit();
        #endif
    }
}
