#pragma once
#include "Components.h"
#include "ECS.h" 

class KeyboardController : public Component //Component jest klasa czysto wirtualna - nadpisujemy jej metody init i update ponizej
{
public:
	TransformComponent *transform; //odpowiada za poruszanie sie
	SpriteComponent *sprite; //odpowiadajace za animacje

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>(); //przypisanie wartosci polom 
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)   //switch opisujacy przemieszczenia/predkosci w ukladzie wspolrzednych / SDL_KEYDOWN - wcisniety klawisz 
		{
			switch (Game::event.key.keysym.sym) //w zaleznosic od klawisza w a s d
			{
			case SDLK_w:
				transform->velocity.y = -1;  // os OY sierowana przeciwnie!
				sprite->Play("Walk"); //funkcja play odpala animacje walk
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
		if (Game::event.type == SDL_KEYUP) //funkcjonalnosc dokladnie przeciwna - w przypadku puszczenia klawisza ruchu
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Idle"); //postac stoi i delikatnie sie rusza
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false; //ustawienie wlaczenie i wylaczenia gry za pomoca klawisza escape

			default:
				break;
			}
		}
	}
};