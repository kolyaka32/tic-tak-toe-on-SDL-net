/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "screamer.hpp"
#include "random"


Screamer::Screamer(const Window& _window)
: Template(_window),
acceptButton(window, 0.5, 0.95, {"Okay...", "Ладно...", "Okay...", "Добра..."}) {
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

void Screamer::update() {
    // Randomly in near 2 minutes
    if (SDL_rand(60*60*5) == 0) {
        // Checking, if not already activated
        if (!active) {
            // Playing 'scary' sound
            sounds.play(Sounds::Screamer);

            // Changing state
            active = true;
            logAdditional("Show screamer");
        }
    }
}

void Screamer::blit() const {
    if (active) {
        // Draw image itself
        window.blit(window.getTexture(Textures::Screamer));

        // Draw exit button
        acceptButton.blit();
    }
}
