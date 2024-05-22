#include "public/InputManager.h"
#include <SDL.h>

// Function that processes incoming bool values with SDL events and checks whether they are printed or not.
void InputManager::KeyControl(bool& _running, bool& _ButtonOneUp, bool& _ButtonOneDown, bool& _ButtonTwoUp, bool& _ButtonTwoDown)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_running = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				_ButtonOneUp = true;
				_ButtonOneDown = false;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				_ButtonOneDown = true;
				_ButtonOneUp = false;
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				_ButtonTwoUp = true;
				_ButtonTwoDown = false;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				_ButtonTwoDown = true;
				_ButtonTwoUp = false;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w)
			{
				_ButtonOneUp = false;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				_ButtonOneDown = false;
			}
			if (event.key.keysym.sym == SDLK_UP)
			{
				_ButtonTwoUp = false;
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				_ButtonTwoDown = false;
			}
		}
	}
}
