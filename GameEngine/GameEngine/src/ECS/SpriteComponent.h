#include "Components.h"
#include "SDL.h"
#include "../TextureMenager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;

	SpriteComponent(const char *path)
	{
		setTex(path);
	}

	SpriteComponent(const char *path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 4, 170);
		Animation walk = Animation(1, 3, 180);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTex(path);
	}

	SpriteComponent(const char *path, const char* animName)
	{
		animated = true;

		Animation idle = Animation(0, 4, 170);
		Animation walk = Animation(1, 3, 180);
		Animation fish = Animation(0, 8, 170);
		Animation waves = Animation(0, 6, 170);
		Animation troll = Animation(0, 2, 300);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Fish", fish);
		animations.emplace("Waves", waves);
		animations.emplace("Troll", troll);

		Play(animName);

		setTex(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char *path)
	{
		texture = TextureMenager::LoadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = transform->height;
		srcRect.w = transform->width;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w*static_cast<int>(SDL_GetTicks() / speed % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.h = transform->height*transform->scale;
		destRect.w = transform->width*transform->scale;
	}

	void draw() override
	{
		TextureMenager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frame;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};