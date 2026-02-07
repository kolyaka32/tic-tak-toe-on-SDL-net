/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveInfo.hpp"


SaveInfo::SaveInfo(const Window& _window, const Field& _field, int _position)
: Template(_window),
backplate(_window, 0.5, _position*0.2f+0.23f, 0.89, 0.2, 15, 2),
//saveNameText(_window, 0.75, position*0.2f+0.16f, {field.getSaveName()}),
lastModifiedText(_window, 0.26, _position*0.2f+0.23f, {_field.getSaveTime()}, 1, Height::Main, WHITE, GUI::Aligment::Left) {
    // Creating texture
    texture = window.createTexture(_field.getWindowWidth(), _field.getWindowWidth());
    window.setRenderTarget(texture);
    // Render full field at it
    _field.blitIcon(window);
    window.resetRenderTarget();
    // Creating position to render it
    dest = {0.08f * window.getWidth(), (_position*0.2f + 0.14f) * window.getHeight(),
        0.18f * window.getWidth(), 0.18f * window.getHeight()};
}

SaveInfo::SaveInfo(SaveInfo&& _info) noexcept
: Template(_info.window),
backplate(std::move(_info.backplate)),
//saveNameText(_info.saveNameText),
lastModifiedText(std::move(_info.lastModifiedText)),
texture(_info.texture) {
    _info.texture = nullptr;
}

SaveInfo::~SaveInfo() {
    if (texture) {
        window.destroy(texture);
    }
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
