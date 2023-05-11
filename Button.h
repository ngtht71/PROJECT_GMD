/*
#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "MainObject.h"

class Button : public MainObject 
{
public:
	ButtonSprite currentSprite;

	Button();

	Button(int x, int y);

	void SetPosition(int x, int y);

	bool IsInside(SDL_Event* e, int size);

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject gButtonTexture);
	void Show(SDL_Renderer* screen);

private:
	SDL_Point position;
};



class PlayerLife : public BaseObject
{
public:
	PlayerLife();
	~PlayerLife(void);

	void SetNum(const int& num) { number_ = num; }
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);
	void Decrease();
private:
	int number_;
	vector<int> position_list_;
};


#endif 
*/