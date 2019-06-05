#include "game.h"
#include "TextureMenager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& stone(manager.addEntity());
auto& ninja(manager.addEntity());
auto& campfire(manager.addEntity());

const char* map_file = "assets/MapTiles.png";

enum groupLabels :std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupTerrain
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& terrain(manager.getGroup(groupTerrain));

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialised! " << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created! " << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created! " << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map();

	//ESC implementation

	Map::LoadMap("assets/map.map", 25, 25);

	stone.addComponent<TransformComponent>(520, 40, 5);
	stone.addComponent<SpriteComponent>("assets/stone.png", false);
	stone.addGroup(groupPlayers);

	campfire.addComponent<TransformComponent>(620, 120, 3);
	campfire.addComponent<SpriteComponent>("assets/campfire.png", true);
	campfire.addGroup(groupPlayers);

	player.addComponent<TransformComponent>(3);
	player.addComponent<SpriteComponent>("assets/player_animations.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	ninja.addComponent<TransformComponent>(100, 100, 3);
	ninja.addComponent<SpriteComponent>("assets/ninjaplayer.png", true);
	ninja.addGroup(groupPlayers);

	
	
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;

	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;

	/*Scrolling tiles ex. platform games

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x *pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y*pSpeed);
	}*/
}



void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto t : tiles)
	{
		t->draw();
	}
	for (auto p : players)
	{
		p->draw();
	}
	for (auto e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned! " << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, map_file);
	tile.addGroup(groupMap);
}