

#include "textures.hpp"


class Window
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Textures textures;
public:
    Window(DataLoader loader);
    ~Window();
};
