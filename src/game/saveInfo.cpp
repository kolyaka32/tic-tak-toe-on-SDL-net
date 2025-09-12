/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveInfo.hpp"


SaveInfo::SaveInfo(const Window& _window, const Field& field, int position)
: Template(_window),
backplate(_window, 0.5, position*0.2f+0.2f, 0.8, 0.2, 5, 2),
saveNameText(_window, 0.75, position*0.2f+0.16f, {field.getSaveName()}),
lastModifiedText(_window, 0.75, position*0.2f+0.33f, {field.getSaveTime()}) {
    // Creating texture
    texture = window.createTexture(field.getWindowWidth(), field.getWindowHeight());
    window.setRenderTarget(texture);
    field.blit(window);
    window.resetRenderTarget();
    // Creating position to rednder it
    dest = {0.2f*window.getWidth(), position*0.2f*window.getHeight(), 0.2f*window.getWidth(), 0.2f*window.getHeight()};
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
