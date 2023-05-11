/*
#pragma once
#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "BaseObject.h"
#include "Button.h"

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick);

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick);

void HandleContinueButton(Button ContinueButton, BaseObject gContinueButtonTexture, SDL_Event* e,
                          SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
                          bool& Game_State, Mix_Chunk* gClick);

void HandlePauseButton(SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
                       Button& PauseButton, Button ContinueButton, BaseObject gContinueButtonTexture,
                       bool& game_state, Mix_Chunk* gClick);


string GetHighScoreFromFile(string path);

void UpdateHighScore(string path, const int& score, const string& old_high_score);

int UpdateGameTimeAndScore(int& time, int& score);

void DrawEndGameSelection(BaseObject gLoseTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again);

void DrawWinGameSelection(BaseObject gWinTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again);

#endif
*/