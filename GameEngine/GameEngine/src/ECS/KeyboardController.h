#pragma once
#include "Components.h"
#include "ECS.h" 

class KeyboardController : public Component
{
public:
	TransformComponent *transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)   //switch opisujacy przemieszczenia/predkosci w ukladzie wspolrzednych 
		{
			switch (Game::event.key.keysym.sym) //w zaleznosic od klawisza w a s d
			{
			case SDLK_w: 
				transform->velocity.y = -1; 
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("Walk");
				break;

			default:
				break;
			}
		}
		//tu bedzie kontynuacja kodu ...