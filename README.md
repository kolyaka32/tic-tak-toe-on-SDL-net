# The standard "Tic-tac-toe" game on c++ using SDL3
[![en](https://img.shields.io/badge/lang-en-green.svg)](README.md)  [![ru](https://img.shields.io/badge/lang-ru-green.svg)](README-ru.md)

This codebase implement standart tic-tac-toe game with cooperative and online mods.

![Screenshot of game](/screenshots/game-main-en.png?raw=true)

## Launching of the game
Download archieve from [releases](https://github.com/kolyaka32/tic-tak-toe-on-SDL-net/releases), depend on platform, unzip and run 'Tic-tak-toe.exe'/'Tic-tak-toe'!

## Usage
Classical game "tic-tac-toe", ported on computer. Rules are simple you need to set crosses or circles at field.
You goal - have pre-set number of your shape in one line/column/diagonal.
As server or first player you can choose, how place first.
Game have 3 mode: 
* Singleplayer (only for field with width 3);
* Local two-person mode (for two people at one machine, walking in turns);
* Internet two person mode (for two people at two different machines, by LAN, UDP);

Also you can change start field configuration and other usefull things from "settings-tic-tac-toe.ini" file.

![Screenshot of extended game](/screenshots/game-extended-en.png?raw=true)

## Supported languages
* English
* Russian (Русский)
* German (Deutsch) (WIP)
* Bellarussian (Беларускі) (WIP)

## License
This project is distributed under the terms of the GNU GENERAL PUBLIC LICENSE v3, available in [LICENSE.txt](LICENSE.txt).

## Platforms
This project has been compiled and tested on several platforms, including:
- Windows (10, 11)
- Ubuntu (22.04)
- Fedora (43)

## Compiling
For use by yourself and validation can check [installation guide](docs/INSTALL.md)

## Bugs
Bug reports are welcome, if you find any, report them [here](https://github.com/kolyaka32/tic-tak-toe-on-SDL-net/issues)

## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/nih-at/libzip
