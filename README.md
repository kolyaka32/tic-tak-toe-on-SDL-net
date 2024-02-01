# The standard  game on c++ using SDL2

This repository contains sources for standart game  I made based on SDL2 library.

![Screenshot of game](/screenshots/game-main.png?raw=true)

## Installing

1. Simply download archieve from [releases](https://github.com/kolyaka32/tic-tak-toe-on-SDL-net/releases), unzip and run 'snake.exe'!
2. Also you can download game installer from [releases](https://github.com/kolyaka32/tic-tak-toe-on-SDL-net/releases).
3. Also you can build project by yourself, watch point 'Instalation for own use'.

## Usage
Classical game "tik-tak toe", ported on computer. Rules are simple you need to set crosses or circles at field.
You goal - have pre-set number of your shape in one line/column/diagonal.
As server or first player you can choose, how place first.
Game have 3 mode: 
* Singleplayer (only if field width equal 3);
* Local two-person mode (for two people at one machine, walking in turns);
* Intrnet two person mode (for two people at two different machines, by LAN);
Also you can change numbers of width, win width and other usefull things from "settings.ini" file.

## Supported languages
* English
* Russian (Русский)

## Instalation for own use
Need external soft:
1. C++ compiler (such as [GCC](https://gcc.gnu.org/releases.html), [MINGW](https://sourceforge.net/projects/mingw/) or [MSYS2](https://www.msys2.org/#installation));
2. [CMake](https://sourceforge.net/projects/cmake.mirror/);
3. External libraries ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer), [SDL ttf](https://github.com/libsdl-org/SDL_ttf), [SDL net](https://github.com/libsdl-org/SDL_net), [libzip](https://github.com/nih-at/libzip));
5. (Optional) [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).

Point 4 with all last builded sources is located at [releases](https://github.com/kolyaka32/tic-tak-toe-on-SDL-net/releases) (Development-kit).

## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip