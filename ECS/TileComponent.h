#pragma once

#include "ECS.h"
#include "SDL2/SDL.h"
#include "Components.h"

class TileComponent : public Component {
	public: 

		SDL_Texture * texture;
		SDL_Rect srcRect, destRect;
		Vector2D position;

		TileComponent() = default;


		TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char * path){
			texture = TextureManager::LoadTexture(path);

			position = Vector2D(xpos, ypos);

			srcRect.x = srcX;
			srcRect.y = srcY;
			srcRect.w = srcRect.h = tsize;

			destRect.x = xpos;
			destRect.y = ypos;
			destRect.h = destRect.w = tsize * tscale;
		}

		void update() override {
			destRect.x = position.x - Game::camera.x;
			destRect.y = position.y - Game::camera.y;

		}

		void draw() override {
			TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
		}

		~TileComponent(){
			SDL_DestroyTexture(texture);
		}
};
