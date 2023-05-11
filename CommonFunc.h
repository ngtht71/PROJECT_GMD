#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>



using namespace std;


#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4


#define IS_REPEATITIVE -1   // cho music ca bai lap
#define NOT_REPEATITIVE 0   // music k lap
#define MIX_CHANNEL -1      // tham so cua music effect 


#define SMALL_BUTTON 1
#define COMMON_BUTTON 2
#define SECOND_BUTTON 3


#define TILE_SIZE 64	
#define BLANK_TILE 0

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define MAX_NUM_DIE 5


const int TIME_INCREASEMENT = 1;
const int TIME_MAX = 1000;


const int COMMON_BUTTON_WIDTH = 270;
const int COMMON_BUTTON_HEIGHT = 270;

const int SECOND_BUTTON_WIDTH = 195;
const int SECOND_BUTTON_HEIGHT = 195;

const int SMALL_BUTTON_WIDTH = 64;
const int SMALL_BUTTON_HEIGHT = 64;

const int PLAY_BUTTON_POSX = 465;	//465-224 (x1-y1)
const int PLAY_BUTTON_POSY = 224;	//726	

const int HELP_BUTTON_POSX = 155;	//155-264	
const int HELP_BUTTON_POSY = 264;	//340 

const int EXIT_BUTTON_POSX = 855;	//855-264
const int EXIT_BUTTON_POSY = 264;	//1045

const int BACK_BUTTON_POSX = 14;	//14,12
const int BACK_BUTTON_POSY = 12;

const int PAUSE_BUTTON_POSX = 14;
const int PAUSE_BUTTON_POSY = 12;

const int CONTINUE_BUTTON_POSX = 14;
const int CONTINUE_BUTTON_POSY = 12;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event event;

//screen
const string WINDOW_TITLE = "GEOMETRY DASH";
const int FRAMES_PER_SECOND = 50;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;


const int RENDER_DRAW_COLOR = 0XFF;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


static char g_name_main[] = { "imgs//player.png" };

typedef struct Input
{
	int right_;
	int jump_;
} Input;


//map1.dat
typedef struct Map {
	int start_x_;
	int start_y_;
	
	int max_x_;
	int max_y_;
	// lưu ô mà nhân vật đang đứng - lấy phần nguyên
	// VD max_x_ = start_x_ / TILE_SIZE

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
}Map;


enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,		//mouse khong inside button
	BUTTON_MOUSE_OVER = 1,		//mouse di chuyen inside button
	BUTTON_TOTAL = 2			// số frame của 1 button
};

void LogError( string msg, int error_code = SDL_ERROR );


string GetHighScoreFromFile(string path);
void UpdateHighScore(string path, const int& score, const string& old_high_score);
int UpdateGameTimeAndScore(int& time, int& score);

#endif