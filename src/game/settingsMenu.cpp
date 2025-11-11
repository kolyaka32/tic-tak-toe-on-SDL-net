/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "settingsMenu.hpp"
#include "../data/cycleTemplate.hpp"


bool SettingsMenu::active = false;

SettingsMenu::SettingsMenu(const Window& _window)
: Template(_window),
settingButton{window, 0.96, 0.05, 0.08, Textures::SettingsButton},
background{window, 0.5, 0.5, 0.65, 0.85, 20, 4},
titleText{window, 0.5, 0.13, {"Pause", "Пауза", "Pause", "Паўза"}, 2, Height::Info},
flags {
    {window, 0.35, 0.27, 0.25, Textures::FlagUSA},
    {window, 0.65, 0.27, 0.25, Textures::FlagRUS},
    {window, 0.35, 0.45, 0.25, Textures::FlagGER},
    {window, 0.65, 0.45, 0.25, Textures::FlagBEL},
},
musicText{window, 0.5, 0.58, {"Music", "Музыка", "Die Musik", "Музыка"}, 1},
musicSlider{window, 0.5, 0.64, 0.5, music.getVolume()},
soundText{window, 0.5, 0.7, {"Sounds", "Звуки", "Geräusche", "Гук"}, 1},
soundSlider{window, 0.5, 0.76, 0.5, sounds.getVolume()},
exitButton{window, 0.5, 0.85, {"Exit", "Выход", "Ausfahrt", "Выхад"}} {}

bool SettingsMenu::click(const Mouse _mouse) {
    mutex.lock();
    // Check, if click on setting butoon
    if (settingButton.in(_mouse)) {
        active ^= true;  // Changing state
        mutex.unlock();
        return false;
    }
    // Clicking in menu
    if (active) {
        // Resetting holding object
        holdingSlider = 0;

        // Check on changing language
        for (unsigned i = 0; i < (unsigned)Language::Count; ++i) {
            if (flags[i].in(_mouse)) {
                if (LanguagedText::setLanguage((Language)i)) {
                    // Changing language
                    window.updateTitle();
                    // Restarting game
                    CycleTemplate::restart();
                    mutex.unlock();
                    return true;
                }
            }
        }
        if (musicSlider.in(_mouse)) {
            holdingSlider = 1;
        } else if (soundSlider.in(_mouse)) {
            holdingSlider = 2;
        } else if (exitButton.in(_mouse)) {
            // Checking on exit
            active = false;
        }
        mutex.unlock();
        return true;
    }
    mutex.unlock();
    return false;
}

void SettingsMenu::unClick() {
    mutex.lock();
    if (active) {
        // Resetting selected box
        holdingSlider = 0;
    }
    mutex.unlock();
}

void SettingsMenu::scroll(const Mouse mouse, float _wheelY) {
    mutex.lock();
    if (active) {
        // Checking scroll on sliders
        if (musicSlider.in(mouse)) {
            music.setVolume(musicSlider.scroll(_wheelY));
            return;
        }
        if (soundSlider.in(mouse)) {
            sounds.setVolume(soundSlider.scroll(_wheelY));
            return;
        }
    }
    mutex.unlock();
}

void SettingsMenu::update() {
    mutex.lock();

    if (active) {
        // Creating and finding mouse position
        Mouse mouse{};

        // Updating pressing on sliders
        switch (holdingSlider) {
        case 1:
            // Updating music slider state
            music.setVolume(musicSlider.setValue(mouse.getX()));
            break;

        case 2:
            // Updating sound slider state
            sounds.setVolume(soundSlider.setValue(mouse.getX()));

            // Playing sound effect for understanding loud
            if (getTime() > nextSound) {
                sounds.play(Sounds::Turn);
                nextSound = getTime() + 400;
            }
            break;
        }
    }
    mutex.unlock();
}

void SettingsMenu::blit() {
    // Draw pause button
    settingButton.blit();

    // Drawing menu if need
    if (active) {
        background.blit();
        titleText.blit();

        // Blitting language buttons
        for (unsigned i = 0; i < 4; ++i) {
            flags[i].blit();
        }
        // Sliders
        musicText.blit();
        soundSlider.blit();
        soundText.blit();
        musicSlider.blit();
        // Quit
        exitButton.blit();
    }
}

void SettingsMenu::activate() {
    // Changing state to opposite
    active ^= true;
}
