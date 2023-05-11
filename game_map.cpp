#include "game_map.h"

GameMap::GameMap() {}
GameMap::~GameMap() {}

void GameMap::LoadMap(char* name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) return;

    game_map.max_x_ = game_map.max_y_ = 0;

    for (int i = 0; i < MAX_MAP_Y; i++)
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf_s(fp, "%d", &game_map.tile[i][j]);
            if (game_map.tile[i][j] > 0)
            {
                if (j > game_map.max_x_) game_map.max_x_ = j;
                if (i > game_map.max_y_) game_map.max_y_ = i;
            }
        }

    game_map.max_x_ = (game_map.max_x_ + 1) * TILE_SIZE;
    game_map.max_y_ = (game_map.max_y_ + 1) * TILE_SIZE;

    game_map.start_x_ = game_map.start_y_ = 0;

    game_map.file_name = name;

    fclose(fp);
}

void GameMap::LoadMapTiles(SDL_Renderer* screen)
{
    char filename[40];
    FILE* fp;

    for (int i = 0; i < MAX_TILES; i++)
    {
        sprintf_s(filename, "map/%d.png", i);

        fopen_s(&fp, filename, "rb");

        if (fp == NULL) continue;

        fclose(fp);

        tile_map[i].LoadImg(filename, screen);
    }
}
    
void GameMap::DrawMap(SDL_Renderer* des)
{
    int map_x = 0;
    int x1 = 0;
    int x2 = 0;

    int map_y = 0;
    int y1 = 0;
    int y2 = 0;
    
    x1 = (game_map.start_x_ % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (game_map.start_y_ % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map.start_x_ / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            if (game_map.tile[map_y][map_x] != 0)
            {
                tile_map [game_map.tile[map_y][map_x]].SetRect(j, i);
                tile_map [game_map.tile[map_y][map_x]].Render(des);
            }
            map_x++;
        }
        map_y++;
    }
}