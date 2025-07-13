
#include <SDL.h>

#include "../dataLoader.hpp"


class Textures
{
private:
    unsigned count;
    SDL_Texture** textures;
public:
    Textures(DataLoader loader, unsigned count, char** texturesNames);
    ~Textures();
};
