/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_iostream.h>
#include "../../../define.hpp"
#include "../../macroses.hpp"
#include "../../exceptions.hpp"


// Interface for load file
class DataLoader {
public:
    DataLoader();
    virtual ~DataLoader();
    virtual SDL_IOStream* load(const char* file) const;
};
