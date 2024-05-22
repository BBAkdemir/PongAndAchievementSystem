#include "public/Pong/ScoreUIElement.h"
#include <string>
#include "public/Pong/Vec2.h"
#include "SDL.h"
#include "public/Scene.h"
#include "SDL_video.h"

ScoreUIElement::ScoreUIElement(Vec2 position, Scene* _Scene) : scene(_Scene)
{
	surface = TTF_RenderText_Solid(scene->scoreFont, "0", { 0xFF, 0xFF, 0xFF, 0xFF });
	texture = SDL_CreateTextureFromSurface(scene->renderer, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = width;
	rect.h = height;
}

ScoreUIElement::~ScoreUIElement()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	scene = nullptr;
}

// Updates the value in the score UI.
void ScoreUIElement::SetScore(int score)
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	surface = TTF_RenderText_Solid(scene->scoreFont, std::to_string(score).c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
	texture = SDL_CreateTextureFromSurface(scene->renderer, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;
}

// Draws the UI on the screen.
void ScoreUIElement::Draw()
{
	SDL_RenderCopy(scene->renderer, texture, nullptr, &rect);
}
