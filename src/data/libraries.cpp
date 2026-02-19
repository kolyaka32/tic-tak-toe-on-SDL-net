/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "libraries.hpp"
// External libraries for initialisation
#if (CHECK_CORRECTION)
#include "exceptions.hpp"
#endif
#include <SDL3/SDL.h>
#if (USE_SDL_FONT)
#include <SDL3_ttf/SDL_ttf.h>
#endif
#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#endif
#include "../internet/library.hpp"


Libraries::Libraries() {
    // Load depend on testing
    #if (CHECK_CORRECTION)
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        throw LibararyLoadException("Main library: " + std::string(SDL_GetError()));
    }

    // Initialasing font library
    #if (USE_SDL_FONT)
    if (!TTF_Init()) {
        throw LibararyLoadException("Font library: " + std::string(SDL_GetError()));
    }
    #endif

    // Initialising audio library
    #if (USE_SDL_MIXER)
    if (!MIX_Init()) {
        throw LibararyLoadException("Couldn't initialise mixer library: " + std::string(SDL_GetError()));
    }
    // Selecting audio device for audio output
    audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (audioDeviceID == 0) {
        throw LibararyLoadException("Couldn't get audio device ID: " + std::string(SDL_GetError()));
    }
    // Creating mixer
    mixer = MIX_CreateMixerDevice(audioDeviceID, nullptr);
    if (mixer == nullptr) {
        throw LibararyLoadException("Couldn't create mixer: " + std::string(SDL_GetError()));
    }
    #endif  // (USE_SDL_MIXER)

    // Intialasing internet library
    #if (USE_NET)
    if (initNet()) {
        throw LibararyLoadException("Couldn't initialase internet library: " + std::string(SDL_GetError()));
    }
    #endif
    logAdditional("Libraries load correctly");

    #else  // (CHECK_CORRECTION)
    // Loading without checking correction

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    #if (USE_SDL_FONT)
    TTF_Init();
    #endif

    #if (USE_SDL_MIXER)
    MIX_Init();
    audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    mixer = MIX_CreateMixerDevice(audioDeviceID, nullptr);
    #endif

    #if (USE_NET)
    initNet();
    #endif

    #endif  // (CHECK_CORRECTION)
}

Libraries::~Libraries() noexcept {
    // Closing internet library
    #if (USE_NET)
    closeNet();
    #endif

    // Closing mixer with audio device
    #if (USE_SDL_MIXER)
    MIX_DestroyMixer(mixer);
    SDL_CloseAudioDevice(audioDeviceID);
    #endif

    // Closing trueTypeFont library
    #if (USE_SDL_FONT)
    TTF_Quit();
    #endif

    // Closing main SDL library
    SDL_Quit();
}

MIX_Mixer* Libraries::getMixer() const {
    return mixer;
}
