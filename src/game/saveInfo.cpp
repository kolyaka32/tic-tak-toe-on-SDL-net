/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveInfo.hpp"


SaveInfo::SaveInfo(const Window& _window, const WindowField& field, int position)
: Template(_window),
backplate(_window, 0.5, position*0.2f+0.2f, 0.8, 0.2, 5, 2),
saveNameText(_window, 0.75, position*0.2f+0.16f, {field.saveName}),
lastModifiedText(_window, 0.75, position*0.2f+0.33f, {"123"}) {
    // Creating texture
    texture = _window.createTexture(field.getWindowWidth(), field.getWindowHeight());
    _window.setRenderTarget(texture);
    field.blit();
    _window.resetRenderTarget();
    // Creating position to rednder it
    dest = {0.2f*_window.getWidth(), position*0.2f*_window.getHeight(), 0.2f*_window.getWidth(), 0.2f*_window.getHeight()};
}

SaveInfo::~SaveInfo() {
    window.destroy(texture);
}

bool SaveInfo::in(Mouse mouse) {
    return mouse.in(dest);
}

void SaveInfo::blit() const {
    backplate.blit();
    window.blit(texture, dest);
    saveNameText.blit();
    lastModifiedText.blit();
}
