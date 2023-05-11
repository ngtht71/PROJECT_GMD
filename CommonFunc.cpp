#include "CommonFunc.h"
#include "TextObject.h"

void LogError(string msg, int error_code)
{
	if (error_code == SDL_ERROR)
		cout << msg << SDL_GetError() << endl;
	
	if (error_code == IMG_ERROR)
		cout << msg << IMG_GetError() << endl;

	if (error_code == MIX_ERROR)
		cout << msg << Mix_GetError() << endl;
	
	if (error_code == TTF_ERROR)
		cout << msg << TTF_GetError() << endl;
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