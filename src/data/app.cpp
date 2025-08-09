/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "cycleTemplate.hpp"
#include "../cycles/gameCycle.hpp"


// Global objects
App app{};
// Selecting loader for data, depend on testing
#if ARCHIEVE_LOADING
const ArchieveLoader dataLoader{};
#else
const StraightLoader dataLoader{};
#endif
// Loaded objects
SoundsData<SND_count> sounds{soundsFilesNames};
MusicData<MUS_count> music{musicFilesNames};
Field GameField::field{};
InitFile initFile{};
Window window{GameField::getWindowWidth(), GameField::getWindowHeight(), {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}};
bool App::running = true;


App::App() {
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
