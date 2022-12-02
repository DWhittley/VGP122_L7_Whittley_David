#include <iostream>
#include <cstdlib>

#include "SDL.h"
#include "SDL_image.h"

// Lab 7 - Matyas & David

using namespace std;

int main(int argv, char** argc)
{
	bool done = false;

	int updatedTime = 0;
	int deltaTime = 6000;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Event event;

	SDL_Texture* bg = nullptr;
	SDL_Texture* logo = nullptr;
	SDL_Texture* playButton = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		cerr << "Unable to initialize SDL " << SDL_GetError() << endl;

		return -1;
	}

	atexit(SDL_Quit);

	window = SDL_CreateWindow("Example 1", 10, 10, 1024, 768, SDL_WINDOW_SHOWN);

	if (!window)
	{
		cerr << "Unable to create window " << SDL_GetError() << endl;

		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		cerr << "Unable to create renderer " << SDL_GetError() << endl;

		return -1;
	}

	bg = IMG_LoadTexture(renderer, "images/bg.png");

	if (!bg)
	{
		cerr << "Unable to create bg image " << IMG_GetError() << endl;

		return -1;
	}

	logo = IMG_LoadTexture(renderer, "images/logo.png");
	
	if (!logo)
	{
		cerr << "Unable to create logo image " << IMG_GetError() << endl;

		return -1;
	}

	playButton = IMG_LoadTexture(renderer, "images/play.png");

	if (!playButton)
	{
		cerr << "Unable to create logo image " << IMG_GetError() << endl;

		return -1;
	}

	SDL_RenderCopy(renderer, bg, nullptr, nullptr);
	SDL_RenderPresent(renderer);

	SDL_Rect dstrect = { 200, 50, 615, 239 };
	SDL_RenderCopy(renderer, logo, nullptr, &dstrect);
	SDL_RenderPresent(renderer);

	SDL_Rect dstrect = { 500, 400, 172, 57 };
	SDL_RenderCopy(renderer, playButton, nullptr, &dstrect);
	SDL_RenderPresent(renderer);

	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_Q)
					done = true;

				break;
			}
		}
	}
	
	SDL_DestroyTexture(playButton);
	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(bg);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}