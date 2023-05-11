
/*
#include "GameUtils.h"

#define TIME_INCREASEMENT 1
#define TIME_MAX 1000

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT) QuitMenu = true;

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;

			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			// MIX_CHANNEL = -1 play on the first free channel, k thanh cong return -1

			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else PlayButton.currentSprite = BUTTON_MOUSE_OUT;
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, SECOND_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else ExitButton.currentSprite = BUTTON_MOUSE_OUT;
}

void HandleContinueButton(Button ContinueButton, BaseObject gContinueButtonTexture,
						  SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
						  bool& Game_State, Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.IsInside(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
					Mix_ResumeMusic();
					Game_State = true;
					Back_To_Game = true;
				}
				break;
				}
			}
			else ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}

void HandlePauseButton(SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
					   Button& PauseButton, Button ContinueButton, BaseObject gContinueButtonTexture,
					   bool& Game_State, Mix_Chunk* gClick)
{
	if (PauseButton.IsInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			Mix_PauseMusic();
			break;
		case SDL_MOUSEBUTTONUP:
			Game_State = false;
			HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, gClick);
			break;
		}
	}
	else 
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
}



string GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path, ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(string path, const int& score, const string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore) oldHighScore = score;
	
	newHighScore = to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

int UpdateGameTimeAndScore(int& time, int& score)
{
	if (time > TIME_MAX) time = 0;

	if (time % 10 == 0) score++;

	time += TIME_INCREASEMENT;

	return time;
}

void DrawEndGameSelection(BaseObject gLoseTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT) Play_Again = false;

				if (e->type == SDL_KEYDOWN)
				{
					End_Game = true;
					Play_Again = false;
					//
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
					//
				}
			}

			gLoseTexture.Render(gRenderer, NULL);

			SDL_RenderPresent(gRenderer);
			gLoseTexture.Free();
		}
	}
	
}

void DrawWinGameSelection(BaseObject gWinTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again)
{
	//gWinTexture.Free();
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT) Play_Again = false;

				if (e->type == SDL_KEYDOWN)
				{
					End_Game = true;
					Play_Again = false;
					/*
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						Play_Again = false;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}//
					

				}
			}

			gWinTexture.Render(gRenderer, NULL);

			SDL_RenderPresent(gRenderer);
			gWinTexture.Free();
		}
	}

}
*/