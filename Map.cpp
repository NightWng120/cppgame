#include "TextureManager.h"
#include "Map.h"
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <fstream>

extern Manager manager;

Map::Map(const char * mfp, int ms, int ts)
	: mapFilePath(mfp), mapScale(ms), tileSize(ts), scaledSize(ts * ms){}

Map::~Map(){
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos){
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);

}

void Map::LoadMap(std::string path, int sizeX, int sizeY){
	char c;
	std::fstream mapFile;
	int srcX;
	int srcY;

	mapFile.open(path);
	for(int y = 0; y < sizeY; y++){
		for(int x = 0; x < sizeX; x++){

			mapFile.get(c);
			srcY = atoi(&c) * tileSize;

			mapFile.get(c);
			srcX = atoi(&c) * tileSize;

			AddTile(srcX, srcY, x*scaledSize, y*scaledSize);
		}
	}
	mapFile.ignore();

	for(int y = 0; y < sizeY; y++){
		for(int x = 0; x < sizeX; x++){

			mapFile.get(c);
			if(c == '1'){
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
		}
	}

	mapFile.close();

}
