/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "cycleTemplate.hpp"
#include "../game/field.hpp"


bool App::running = true;

App::App(const LanguagedText _title)
: music{loader, musicFilesNames},
sounds{loader, soundsFilesNames},
initFile(music, sounds),
window{loader, Field::getWindowWidth(), Field::getWindowHeight(), _title} {
    #if CHECK_CORRECTION
    SDL_Log("All loaded and created corretly");
    #endif
}

void App::stop() {
    running = false;
    CycleTemplate::stop();
}

bool App::isRunning() {
    return running;
}
