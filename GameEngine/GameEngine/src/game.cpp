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

auto& fish(manager.addEntity());
auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& stone(manager.addEntity());
auto& campfire(manager.addEntity());
auto& tree(manager.addEntity());
auto& tent(manager.addEntity());
auto& waves2(manager.addEntity());
auto& ship(manager.addEntity());
auto& jacsparrow(manager.addEntity());
auto& pirateship(manager.addEntity());
auto& pirate2(manager.addEntity());
auto& troll(manager.addEntity());

const char* map_file = "assets/MapTiles.png";

enum groupLabels :std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupTerrain
};


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
	stone.addGroup(groupTerrain);

	campfire.addComponent<TransformComponent>(620, 120, 3);
	campfire.addComponent<SpriteComponent>("assets/campfire.png", true);
	campfire.addGroup(groupTerrain);

	tree.addComponent<TransformComponent>(640, 15, 5);
	tree.addComponent<SpriteComponent>("assets/tree.png", false);
	tree.addGroup(groupTerrain);

	tent.addComponent<TransformComponent>(750, 75, 5);
	tent.addComponent<SpriteComponent>("assets/tent.png", false);
	tent.addGroup(groupTerrain);

	tree.addComponent<TransformComponent>(1000, 150, 5);
	tree.addComponent<SpriteComponent>("assets/tree.png", false);
	tree.addGroup(groupTerrain);

	tree.addComponent<TransformComponent>(800, 340, 5);
	tree.addComponent<SpriteComponent>("assets/tree.png", false);
	tree.addGroup(groupTerrain);

	waves2.addComponent<TransformComponent>(140, 120, 2);
	waves2.addComponent<SpriteComponent>("assets/waves2.png", "Waves");
	waves2.addGroup(groupTerrain);

	waves2.addComponent<TransformComponent>(450, 300, 3);
	waves2.addComponent<SpriteComponent>("assets/waves2.png", "Waves");
	waves2.addGroup(groupTerrain);

	waves2.addComponent<TransformComponent>(10, 230, 2);
	waves2.addComponent<SpriteComponent>("assets/waves2.png", "Waves");
	waves2.addGroup(groupTerrain);

	waves2.addComponent<TransformComponent>(60, 300, 3);
	waves2.addComponent<SpriteComponent>("assets/waves2.png", "Waves");
	waves2.addGroup(groupTerrain);

	waves2.addComponent<TransformComponent>(190, 600, 2);
	waves2.addComponent<SpriteComponent>("assets/waves2.png", "Waves");
	waves2.addGroup(groupTerrain);

	ship.addComponent<TransformComponent>(500, 180, 7);
	ship.addComponent<SpriteComponent>("assets/ship.png", false);
	ship.addGroup(groupTerrain);

	jacsparrow.addComponent<TransformComponent>(1250, 200, 3);
	jacsparrow.addComponent<SpriteComponent>("assets/jacsparrow.png", false);
	jacsparrow.addGroup(groupTerrain);

	pirateship.addComponent<TransformComponent>(1320, 50, 8);
	pirateship.addComponent<SpriteComponent>("assets/piratesship.png", false);
	pirateship.addGroup(groupTerrain);

	pirate2.addComponent<TransformComponent>(1350, 250, 4);
	pirate2.addComponent<SpriteComponent>("assets/pirate2.png", false);
	pirate2.addGroup(groupTerrain);

	fish.addComponent<TransformComponent>(130, 300, 2);
	fish.addComponent<SpriteComponent>("assets/fish.png", "Fish");
	fish.addGroup(groupEnemies);

	player.addComponent<TransformComponent>(3);
	player.addComponent<SpriteComponent>("assets/player_animations.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	troll.addComponent<TransformComponent>(500, 900, 4);
	troll.addComponent<SpriteComponent>("assets/troll.png", "Troll");
	troll.addGroup(groupEnemies);

	troll.addComponent<TransformComponent>(600, 865, 3);
	troll.addComponent<SpriteComponent>("assets/corpse.png", false);
	troll.addGroup(groupEnemies);

	troll.addComponent<TransformComponent>(600, 930, 3);
	troll.addComponent<SpriteComponent>("assets/chest.png", false);
	troll.addGroup(groupEnemies);

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

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& terrain(manager.getGroup(groupTerrain));


void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto t : tiles)
	{
		t->draw();
	}

	for (auto t : terrain)
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