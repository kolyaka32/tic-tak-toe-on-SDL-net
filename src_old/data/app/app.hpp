#pragma once


#include "dataLoader.hpp"
#include "music.hpp"
#include "sounds.hpp"
#include "screen/screen.hpp"


class App
{
private:
    /* data */
    DataLoader dataLoader;
public:
    App(/* args */);
    ~App();

    Music music;
    Sounds sounds;
    Screen screen;
};

extern App app;
