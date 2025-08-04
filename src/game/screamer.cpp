/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "screamer.hpp"
#include "random"


Screamer::Screamer(const Window& _target)
: acceptButton(_target, 0.5, 0.95, {"Okay...", "Ладно...", "Okay...", "Добра..."}, 24) {
    SDL_srand(0);
}

bool Screamer::click(const Mouse _mouse) {
    if (active) {
        // Check on button
        if (acceptButton.in(_mouse)) {
            active = false;
        }
        return true;
    }
    return false;
}

void Screamer::update(const Sounds& _sound) {
    // Randomly in near 2 minutes
    if (SDL_rand(60*60) == 0) {
        // Checking, if not already activated
        if (!active) {
            active = true;
            // Playing 'scary' sound
            _sound.play(SND_SCREAMER);
        }
    }
}

void Screamer::blit(const Window& _target) const {
    if (active) {
        // Draw image itself
        _target.blit(IMG_SCREAMER);

        // Draw exit button
        acceptButton.blit(_target);
    }
}
