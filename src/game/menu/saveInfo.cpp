/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveInfo.hpp"


SaveInfo::SaveInfo(const Window& _window, const Field& field, int position)
: Template(_window),
backplate(_window, 0.5, position*0.2f+0.23f, 0.89, 0.2, 15, 2),
//saveNameText(_window, 0.75, position*0.2f+0.16f, {field.getSaveName()}),
lastModifiedText(_window, 0.26, position*0.2f+0.23f, {field.getSaveTime()}, 1, Height::Main, WHITE, GUI::Aligment::Left) {
    // Creating texture
    texture = window.createTexture(field.getWindowWidth(), field.getWindowWidth());
    window.setRenderTarget(texture);
    field.blitIcon(window);
    window.resetRenderTarget();
    // Creating position to rednder it
    dest = {0.08f*window.getWidth(), (position*0.2f+0.14f)*window.getHeight(), 0.18f*window.getWidth(), 0.18f*window.getHeight()};
}

SaveInfo::~SaveInfo() {
    window.destroy(texture);
}

void SaveInfo::moveUp() {
    backplate.move(0, -0.2);
    lastModifiedText.move(0, -0.2);
    dest.y -= 0.2*window.getHeight();
}

void SaveInfo::moveDown() {
    backplate.move(0, 0.2);
    lastModifiedText.move(0, 0.2);
    dest.y += 0.2*window.getHeight();
}

bool SaveInfo::in(Mouse _mouse) const {
    return backplate.in(_mouse);
}

void SaveInfo::blit() const {
    backplate.blit();
    window.blit(texture, dest);
    //saveNameText.blit();
    lastModifiedText.blit();
}
