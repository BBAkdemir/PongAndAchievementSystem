#pragma once

#include <iostream>
#include <memory.h>
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "SDL_surface.h"
#include "SDL_rect.h"

class Vec2;
class Scene;

class ScoreUIElement
{
public:

	ScoreUIElement(Vec2 position, Scene* _Scene);
	~ScoreUIElement();

	// Updates the value in the score UI.
	void SetScore(int score);
	// Draws the UI on the screen.
	void Draw();

	Scene* scene;
	SDL_Surface* surface{};
	SDL_Texture* texture{};
	SDL_Rect rect{};
};

