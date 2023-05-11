#pragma once
#include "BaseObject.h"

class PlayerLife : public BaseObject
{
public:
	PlayerLife();
	~PlayerLife(void);

	void SetNum(const int& num) { number_ = num; }
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);
	void InitPause(SDL_Renderer* screen);
	void Decrease();
private:
	int number_;
	vector<int> position_list_;
};
