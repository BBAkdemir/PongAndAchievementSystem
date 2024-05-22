#pragma once

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "SDL_surface.h"
#include "SDL_rect.h"
#include "SDL_image.h"
#include <string>

#include <iostream>
#include <memory.h>
#include "SimpleGameTypes.h"

using std::string;

class Vec2;
class Scene;

// This class is the main class of achievement UI.
class UIElement
{
public:

	UIElement(Vec2 position, Scene* _Scene, eGameSide _PlayerSide, string _ImagePath, string _Title, string _Text, float _DestroyTime);
	~UIElement();

	// Draws the UI on the screen. If "currentLifeTime" is greater than "destroyTime", it returns true and is destroyed.
	bool Draw(float dt);

	Scene* scene;
	SDL_Surface* imageSurface{};
	SDL_Surface* titleSurface{};
	SDL_Surface* descriptionSurface{};
	SDL_Surface* playerNameSurface{};

	SDL_Texture* imageTexture{};
	SDL_Texture* titleTexture{};
	SDL_Texture* descriptionTexture{};
	SDL_Texture* playerNameTexture{};

	SDL_Rect imageRect{};
	SDL_Rect titleRect{};
	SDL_Rect descriptionRect{};
	SDL_Rect playerNameRect{};

	// time value that holds when the created UI will be deleted from the screen.
	float destroyTime;
	// The time the created UI stays on the screen
	float currentLifeTime = 0;
};