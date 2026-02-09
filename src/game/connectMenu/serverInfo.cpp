/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverInfo.hpp"


ServerInfo::ServerInfo(const Window& _window, int _position, const ServerData& _data)
: backplate(_window, 0.48, _position*0.15f, 1.0, 0.15, 20, 2) {
    
}

ServerInfo::ServerInfo(ServerInfo&& _info) noexcept
: backplate(std::move(_info.backplate)) {}

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
