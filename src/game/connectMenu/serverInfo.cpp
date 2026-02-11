/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverInfo.hpp"


ServerInfo::ServerInfo(const Window& _window, int _position, const ServerData& _data)
: backplate(_window, 0.48, _position*0.14f+0.1, 1.0, 0.14, 20, 2),
addressText(_window, 0.1, _position*0.14f+0.03, {"%s:%d"},
    Height::Main, WHITE, GUI::Aligment::Left, _data.getAddress().getName(), _data.getAddress().getPort()),
pingText(_window, 0.1, _position*0.14f+0.11, {"Ping: %d"},
    Height::Main, WHITE, GUI::Aligment::Left, _data.getPing()) {

}

ServerInfo::ServerInfo(ServerInfo&& _object) noexcept
: backplate(std::move(_object.backplate)),
addressText(std::move(_object.addressText)),
pingText(std::move(_object.pingText)) {}

ServerInfo::~ServerInfo() noexcept {
    
}

void ServerInfo::moveUp() {
    backplate.move(0.0, -0.2);
}

void ServerInfo::moveDown() {
    backplate.move(0.0, 0.2);
}

void ServerInfo::blit() const {
    backplate.blit();
}

bool ServerInfo::in(Mouse _mouse) const {
    return backplate.in(_mouse);
}
