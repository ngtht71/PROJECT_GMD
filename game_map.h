#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMap:public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};


class GameMap
{
public:
	GameMap();
	~GameMap();
	void LoadMap(char* name);
	void DrawMap(SDL_Renderer* des);
	void LoadMapTiles(SDL_Renderer* screen);
	Map GetMap() const { return game_map; }
	void SetMap(const Map& gMap) { game_map = gMap; }
private:
	Map game_map;
	TileMap tile_map[MAX_TILES];
};
#endif