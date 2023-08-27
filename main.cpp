//C++ Standard Libraries
#include <iostream>
#include "SDL2/SDL.h"
#include "Game.h"

Game * game = nullptr;

int main(int argc, char * argv[]){

	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while(game->running()){

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();

	return 0;
}
/*
 * while(game is running){
 * 		handle any user input
 * 		update all objects, eg. positions, etc
 * 		render changes to display
 * {
*/



//int main(int argc, char * argv[]){
//	SDL_Init(SDL_INIT_EVERYTHING);
//	SDL_Window * window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
//	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
//
//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//	SDL_RenderClear(renderer);
//
//	SDL_RenderPresent(renderer);
//
//	SDL_Delay(3000);
//
//
//	//std::cout << "We do be out here\n";
//}
