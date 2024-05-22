#include "public/RewardUIElement.h"

#include "public/Pong/ScoreUIElement.h"
#include "public/Pong/Vec2.h"
#include "public/Scene.h"

#include "SDL_video.h"
#include "SDL.h"

RewardUIElement::RewardUIElement(Vec2 position, Scene* _Scene, string _ImagePath) : scene(_Scene)
{
	imageSurface = IMG_Load(_ImagePath.c_str());
	imageTexture = SDL_CreateTextureFromSurface(_Scene->renderer, imageSurface);

	countSurface = TTF_RenderText_Solid(scene->scoreFont, "0", {0xFF, 0xFF, 0xFF, 0xFF});
	countTexture = SDL_CreateTextureFromSurface(_Scene->renderer, countSurface);

	int width, height;
	SDL_QueryTexture(imageTexture, nullptr, nullptr, &width, &height);

	imageRect.x = static_cast<int>(position.x);
	imageRect.y = static_cast<int>(position.y);
	imageRect.w = width;
	imageRect.h = height;

	SDL_QueryTexture(countTexture, nullptr, nullptr, &width, &height);

	countRect.x = static_cast<int>(position.x) + 50;
	countRect.y = static_cast<int>(position.y);
	countRect.w = width * 0.8f;
	countRect.h = height * 0.8f;
}

RewardUIElement::~RewardUIElement()
{
	SDL_FreeSurface(imageSurface);
	SDL_DestroyTexture(imageTexture);
	SDL_FreeSurface(countSurface);
	SDL_DestroyTexture(countTexture);
}

// Updates the value in the score UI.
void RewardUIElement::SetCount(int _Count)
{
	SDL_FreeSurface(countSurface);
	SDL_DestroyTexture(countTexture);

	countSurface = TTF_RenderText_Solid(scene->scoreFont, std::to_string(_Count).c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
	countTexture = SDL_CreateTextureFromSurface(scene->renderer, countSurface);

	int width, height;
	SDL_QueryTexture(countTexture, nullptr, nullptr, &width, &height);
	countRect.w = width * 0.8f;
	countRect.h = height * 0.8f;
}

// Draws the UI on the screen.
void RewardUIElement::Draw()
{
	SDL_RenderCopy(scene->renderer, imageTexture, nullptr, &imageRect);
	SDL_RenderCopy(scene->renderer, countTexture, nullptr, &countRect);
}
