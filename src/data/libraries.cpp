/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "libraries.hpp"
// External libraries for initialisation
#include <SDL3/SDL.h>
#if (USE_SDL_FONT)
#include <SDL3_ttf/SDL_ttf.h>
#endif
#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#endif
#if (CHECK_CORRECTION)
#include "exceptions.hpp"
#endif
#if (USE_SDL_NET)
#include <SDL3_net/SDL_net.h>
#endif


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
    // Initialasing audio library
    #if (USE_SDL_MIXER)
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK)) {
        throw LibararyLoadException("Mixer library: " + std::string(SDL_GetError()));
    }
    // Starting audio
    audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (audioDeviceID == 0) {
        throw LibararyLoadException("Couldn't get audio device ID: " + std::string(SDL_GetError()));
    }
    // Openning audio chanel
    if (!Mix_OpenAudio(audioDeviceID, NULL)) {
        throw LibararyLoadException("Couldn't initialase audio chanel: " + std::string(SDL_GetError()));
    }
    #endif
    // Intialasing internet library
    #if (USE_SDL_NET)
    if (!NET_Init()) {
        throw LibararyLoadException("Couldn't initialase internet library: " + std::string(SDL_GetError()));
    }
    #endif

    logAdditional("Libraries load correctly");
    #else  // (CHECK_CORRECTION)
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    #if (USE_SDL_FONT)
    TTF_Init();
    #endif
    #if (USE_SDL_MIXER)
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
    audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    Mix_OpenAudio(audioDeviceID, NULL);
    #endif
    #if (USE_SDL_NET)
    NET_Init();
    #endif
    #endif  // (CHECK_CORRECTION)
}

Libraries::~Libraries() noexcept {
    // Closing internet library
    #if (USE_SDL_NET)
    NET_Quit();
    #endif

    // Closing audio device
    #if (USE_SDL_MIXER)
    Mix_CloseAudio();
    SDL_CloseAudioDevice(audioDeviceID);
    #endif

    // Closing all library reversed
    #if (USE_SDL_MIXER)
    Mix_CloseAudio();
    #endif
    #if (USE_SDL_FONT)
    TTF_Quit();
    #endif
    // Closing main SDL library
    SDL_Quit();
}
