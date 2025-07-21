/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "settingsMenu.hpp"


bool SettingsMenu::active = false;

SettingsMenu::SettingsMenu(const App& _app)
: settingButton{_app.window, 0.95, 0.05, IMG_GUI_PAUSE_BUTTON},
background{_app.window, 0.5, 0.5, 0.65, 0.85, 20, 5},
titleText{_app.window, 0.5, 0.13, {"Pause", "Пауза", "Pause", "Паўза"}, 2, 30, WHITE},
flags {
    {_app.window, 0.35, 0.27, IMG_GUI_FLAG_USA},
    {_app.window, 0.65, 0.27, IMG_GUI_FLAG_RUS},
    {_app.window, 0.35, 0.45, IMG_GUI_FLAG_GER},
    {_app.window, 0.65, 0.45, IMG_GUI_FLAG_BEL},
},
/*musicText{_app.window, 0.5, 0.58, {"Music", "Музыка", "Die Musik", "Музыка"}, 1, 24, WHITE},
musicSlider{_app.window, 0.5, 0.64, _app.music.getVolume()},
soundText{_app.window, 0.5, 0.7, {"Sounds", "Звуки", "Geräusche", "Гук"}, 1, 24, WHITE},
soundSlider{_app.window, 0.5, 0.76, _app.sounds.getVolume()},*/
exitButton{_app.window, 0.5, 0.85, {"Exit", "Выход", "Ausfahrt", "Выхад"}, 24, WHITE} {}

bool SettingsMenu::click(const Mouse _mouse, const App& _app) {
    // Check, if click on setting butoon
    if (settingButton.in(_mouse)) {
        active ^= true;  // Changing state
        return false;
    }
    // Clicking in menu
    if (active) {
        // Check on changing language
        for (unsigned i = 0; i < (unsigned)Language::Count; ++i) {
            if (flags[i].in(_mouse)) {
                if (LanguagedText::setLanguage((Language)i)) {
                    // Changing language
                    _app.window.updateTitle();
                    // Restarting game
                    CycleTemplate::restart();
                    return true;
                }
            }
        }
        /* if (musicSlider.in(_mouse)) {
            // Checking, if click on sliders or flag
            holdingSlider = 1;
            return true;
        }
        if (soundSlider.in(_mouse)) {
            holdingSlider = 2;
            return true;
        }*/
        if (exitButton.in(_mouse)) {
            // Checking on exit
            active = false;
            return true;
        }
        return true;
    }
    return false;
}

void SettingsMenu::unClick() {
    if (active) {
        // Resetting selected box
        holdingSlider = 0;
    }
}

void SettingsMenu::scroll(App& _app, const Mouse mouse, float _wheelY) {
    if (active) {
        // Checking scroll on sliders
        /*if (musicSlider.in(mouse)) {
            _app.music.setVolume(musicSlider.scroll(_wheelY));
            return;
        }
        if (soundSlider.in(mouse)) {
            _app.sounds.setVolume(soundSlider.scroll(_wheelY));
            return;
        }*/
    }
}

void SettingsMenu::update(App& _app) {
    if (active) {
        // Creating and finding mouse position
        /*Mouse mouse;
        mouse.updatePos();

        // Updating pressing on sliders
        switch (holdingSlider) {
        case 1:
            // Updating music slider state
            _app.music.setVolume(musicSlider.setValue(mouse.getX()));
            break;

        case 2:
            // Updating sound slider state
            _app.sounds.setVolume(soundSlider.setValue(mouse.getX()));

            // Playing sound effect for understanding loud
            if (getTime() > nextSound) {
                //_app.sounds.play(SND_TURN);
                nextSound = getTime() + 400;
            }
            break;
        }*/
    }
}

void SettingsMenu::blit(const Window& _target) const {
    // Draw pause button
    settingButton.blit(_target);

    // Drawing menu if need
    if (active) {
        background.blit(_target);
        titleText.blit(_target);

        // Blitting language buttons
        for (unsigned i = 0; i < 4; ++i) {
            flags[i].blit(_target);
        }
        // Sliders
        /*musicText.blit(_target);
        soundSlider.blit(_target);
        soundText.blit(_target);
        musicSlider.blit(_target);*/
        // Quit
        exitButton.blit(_target);
    }
}

void SettingsMenu::activate() {
    // Changing state to opposite
    active ^= true;
}
