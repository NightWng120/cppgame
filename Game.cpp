#include <iostream>
#include "Game.h"
#include "TextureManager.cpp"
#include "Map.cpp"
#include "ECS/ECS.cpp"
#include "ECS/Components.h"
#include "Collision.cpp"

SDL_Renderer* Game::renderer = nullptr;
Map * map;


Manager manager;

SDL_Event Game::event;
bool Game::isRunning = false;
SDL_Rect Game::camera = {0, 0, 800, 640};
//Entity& player = manager.addEntity();

auto& player(manager.addEntity());



//auto& enemies(manager.getGroup(Game::groupEnemies));

Game::Game(){
}

Game::~Game(){
}

void Game::init(const char * title, int width, int height, bool fullscreen){
	int flags = 0;
	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING ) == 0){

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		//if(window){
		//	std::cout << "Window created\n";
		//}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			//std::cout << "Renderer created\n";
		}

		isRunning = true;
	}
	map = new Map("assets/terrain_ss.png", 3, 32);

	map->LoadMap("assets/map.map", 25, 20);
	player.addComponent<TransformComponent>(400, 320, 32, 32, 3);
	player.addComponent<SpriteComponent>("assets/animations.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(Game::groupPlayers);

	//wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	//wall.addComponent<SpriteComponent>("assets/dirt.png");
	//wall.addComponent<ColliderComponent>("wall");
	//wall.addGroup(Game::groupMap);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents(){



	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
		default:
			break;
	}


}

void Game::update(){

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos= player.getComponent<TransformComponent>().position;

	manager.update();
	manager.refresh();

	for(auto& c : colliders){
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if(Collision::AABB(player.getComponent<ColliderComponent>().collider, cCol)){
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}              
	
	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320; 

	if(camera.x < 0)
		camera.x = 0;
	if(camera.y < 0)
		camera.y = 0;

	if(camera.x > camera.w)
		camera.x = camera.w;
	if(camera.y > camera.h)
		camera.y = camera.h;

	//for(auto cc: game::colliders){
	//	if(cc != &player.getcomponent<collidercomponent>() && collision::aabb(player.getcomponent<collidercomponent>(), *cc)){

	//		//player.getcomponent<transformcomponent>().scale = 1;
	//		player.getcomponent<transformcomponent>().velocity * -1;

	//	}

	//}
	//std::cout << player.getcomponent<transformcomponent>().position << std::endl;
}


void Game::render(){
	SDL_RenderClear(renderer);
	for(auto& t : tiles){
		t->draw();
	}

	for(auto& c : colliders){
		c->draw();
	}

	for(auto& p : players){
		p->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned\n";
}


