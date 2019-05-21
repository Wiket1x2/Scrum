#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent *transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}
};
