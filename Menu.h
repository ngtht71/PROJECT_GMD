#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "BaseObject.h"
#include "CommonFunc.h"

using namespace std;

class Menu
{
public:
    Menu(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    ~Menu();
    
    int screenW, screenH;
    int optionsNumber, optionChoosen;
    int transVelo;
    int instructionDistance;
    int blinkTimes;

    bool in_menu;
    bool doneTransition;
    bool menuToInstruction;

    bool exit_game;


    SDL_Texture* menuTexture;

    SDL_Texture* play, * playChoosen, * instruction, * instructionChoosen;
    SDL_Rect playPos, instructionPos;

    SDL_Texture* exit, *exitChoosen;
    SDL_Rect exitPos;

    SDL_Texture* ins1, * ins2;
    SDL_Rect ins1Pos, ins2Pos;

    SDL_Texture* Right, * Left;
    SDL_Rect RightPos, LeftPos;

    SDL_Texture* Return;
    SDL_Rect ReturnPos, ReturnRect;

    SDL_Texture* buttonInstruction;
    SDL_Rect buttonInstructionPos, buttonInstructionRect;

    Mix_Music* menuMusic;

    Uint32 frameTime;
    Uint32 blinkingTime;

    void loadMenuIMG(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& e);
    void render(SDL_Renderer* renderer);
};

void DrawEndGameSelection(BaseObject gLoseTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again, bool& in_menu);
void DrawWinGameSelection(BaseObject gLoseTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again);

#endif
