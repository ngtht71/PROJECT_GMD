#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	virtual bool LoadImg(string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	
	void Free();
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; };
	// set giá trị cho rect
	
	SDL_Rect GetRect() const { return rect_; }
	// lấy ra rect
	
	SDL_Texture* GetObject() { return p_object_; }
	// lấy ra object

	static SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
	// rect có int x, y, w, h;
};


#endif