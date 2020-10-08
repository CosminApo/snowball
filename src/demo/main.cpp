#include <snowball/core.h>
#include <iostream>
#include <SDL.h>


int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

using namespace snowball;

int main(int argc, char* argv[])
{
#pragma region testing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        680, 480,
        0);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);
#pragma endregion

    std::shared_ptr<Core> core = Core::initialize();
	
	std::cout << "Hello world" << std::endl;


	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}