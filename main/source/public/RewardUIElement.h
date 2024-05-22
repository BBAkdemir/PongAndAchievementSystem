#pragma once

#include <iostream>
#include <memory.h>
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "SDL_surface.h"
#include "SDL_rect.h"
#include <string>

using std::string;

class Vec2;
class Scene;

class RewardUIElement
{
public:

	RewardUIElement(Vec2 position, Scene* _Scene, string _ImagePath);
	~RewardUIElement();

	// Updates the value in the score UI.
	void SetCount(int _Count);
	// Draws the UI on the screen.
	void Draw();

	Scene* scene;
	SDL_Surface* imageSurface{};
	SDL_Surface* countSurface{};

	SDL_Texture* imageTexture{};
	SDL_Texture* countTexture{};

	SDL_Rect imageRect{};
	SDL_Rect countRect{};
};

