#include "UIElement.h"

#include "public/Pong/ScoreUIElement.h"
#include "public/Pong/Vec2.h"
#include "public/Scene.h"

#include "SDL_video.h"
#include "SDL.h"

UIElement::UIElement(Vec2 position, Scene* _Scene, eGameSide _PlayerSide, string _ImagePath, string _Title, string _Text, float _DestroyTime) : scene(_Scene), destroyTime(_DestroyTime)
{
	imageSurface = IMG_Load(_ImagePath.c_str());
	imageTexture = SDL_CreateTextureFromSurface(_Scene->renderer, imageSurface);
	
	titleSurface = TTF_RenderText_Solid(scene->scoreFont, _Title.c_str(), {0xFF, 0xFF, 0xFF, 0xFF});
	titleTexture = SDL_CreateTextureFromSurface(_Scene->renderer, titleSurface);

	descriptionSurface = TTF_RenderText_Solid_Wrapped(scene->scoreFont, _Text.c_str(), { 0xFF, 0xFF, 0xFF, 0xFF }, 600);
	descriptionTexture = SDL_CreateTextureFromSurface(_Scene->renderer, descriptionSurface);

	string name;
	if (_PlayerSide == eGameSide::PLAYER)
		name = "PlayerOne";
	else
		name = "PlayerTwo";

	playerNameSurface = TTF_RenderText_Solid(scene->scoreFont, name.c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
	playerNameTexture = SDL_CreateTextureFromSurface(_Scene->renderer, playerNameSurface);
	
	int width, height;
	SDL_QueryTexture(imageTexture, nullptr, nullptr, &width, &height);

	imageRect.x = static_cast<int>(position.x) - (width * 1.3f) - 200;
	imageRect.y = static_cast<int>(position.y) - (height * 1.3f);
	imageRect.w = width * 1.3f;
	imageRect.h = height * 1.3f;

	SDL_QueryTexture(titleTexture, nullptr, nullptr, &width, &height);

	titleRect.x = static_cast<int>(position.x) - 190;
	titleRect.y = static_cast<int>(position.y) - 50 * 1.3f;
	titleRect.w = width * 0.4f;
	titleRect.h = height * 0.4f;

	SDL_QueryTexture(descriptionTexture, nullptr, nullptr, &width, &height);

	descriptionRect.x = static_cast<int>(position.x) - 190;
	descriptionRect.y = static_cast<int>(position.y) - 45;
	descriptionRect.w = width * 0.3f;
	descriptionRect.h = height * 0.3f;

	SDL_QueryTexture(playerNameTexture, nullptr, nullptr, &width, &height);

	playerNameRect.x = static_cast<int>(position.x) - 200;
	playerNameRect.y = static_cast<int>(position.y) - 90;
	playerNameRect.w = width * 0.4f;
	playerNameRect.h = height * 0.4f;
}

UIElement::~UIElement()
{
	SDL_FreeSurface(imageSurface);
	SDL_DestroyTexture(imageTexture);
	SDL_FreeSurface(titleSurface);
	SDL_DestroyTexture(titleTexture);
	SDL_FreeSurface(descriptionSurface);
	SDL_DestroyTexture(descriptionTexture);
	SDL_FreeSurface(playerNameSurface);
	SDL_DestroyTexture(playerNameTexture);
}

// Draws the UI on the screen. If "currentLifeTime" is greater than "destroyTime", it returns true and is destroyed.
bool UIElement::Draw(float dt)
{
	SDL_RenderCopy(scene->renderer, imageTexture, nullptr, &imageRect);
	SDL_RenderCopy(scene->renderer, titleTexture, nullptr, &titleRect);
	SDL_RenderCopy(scene->renderer, descriptionTexture, nullptr, &descriptionRect);
	SDL_RenderCopy(scene->renderer, playerNameTexture, nullptr, &playerNameRect);
	currentLifeTime += dt;
	if (currentLifeTime >= destroyTime)
	{
		std::cout << " silindii\n";
		return true;
	}
	return false;
}