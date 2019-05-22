#pragma once
#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureMenager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.h = srcRect.w = 32;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.h = destRect.w = 64;
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureMenager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};