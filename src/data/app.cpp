/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "cycleTemplate.hpp"


bool App::running = true;
std::mutex App::startMutex{};

void App::stop() {
    running = false;
    CycleTemplate::stop();
    logAdditional("Stop running current app");
}

bool App::isRunning() {
    return running;
}

void App::waitStart() {
    // Waiting, until mutex will be avaliable
    startMutex.lock();
    // Unlocking it for next cycles
    startMutex.unlock();
}

void App::start() {
    startMutex.unlock();
}

void App::startNext(const Cycle _nextCycle) {
    logAdditional("Start next cycle: %d", _nextCycle);
    nextCycle = _nextCycle;
}
