/*
#include "Button.h"

Button::Button()
{
    position.x = 0;
    position.y = 0;
    currentSprite = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y)
{
    position.x = x;
    position.y = y;
    currentSprite = BUTTON_MOUSE_OUT;
}

void Button::SetPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

bool Button::IsInside(SDL_Event* e, int size)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        int button_width, button_height;
        if (size == SMALL_BUTTON)
        {
            button_width = SMALL_BUTTON_WIDTH;
            button_height = SMALL_BUTTON_HEIGHT;
        }
        else if (size == COMMON_BUTTON)
        {
            button_width = COMMON_BUTTON_WIDTH;
            button_height = COMMON_BUTTON_HEIGHT;
        }
        else 
        {
            button_width = SECOND_BUTTON_WIDTH;
            button_height = SECOND_BUTTON_HEIGHT;
        }

        SDL_GetMouseState(&x, &y);

        bool inside = true;
        if (x < position.x)  inside = false;

        else if (x > position.x + button_width)
            inside = false;

        else if (y < position.y)
            inside = false;

        else if (y > position.y + button_height)
            inside = false;

        return inside;
    }
    return false;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject gButtonTexture)
{
    gButtonTexture.RenderButton(position.x, position.y, gRenderer, currentClip);
}


void Button::Show(SDL_Renderer* screen)
{
    LoadImg("imgs/button/big_button/paused-1.png", screen);

    rect_.x = PAUSE_BUTTON_POSX;
    rect_.y = PAUSE_BUTTON_POSY;

    BaseObject::Render(screen);
}





PlayerLife::PlayerLife() { number_ = 0; }
PlayerLife::~PlayerLife(void) {}

void PlayerLife::AddPos(const int& xPos){ position_list_.push_back(xPos);}

void PlayerLife::Init(SDL_Renderer* screen)
{
    LoadImg("imgs//heart.png", screen);
    number_ = MAX_NUM_DIE;
    if (position_list_.size() > 0) 
        position_list_.clear();

    AddPos(140);
    AddPos(180);
    AddPos(220);
    AddPos(260);
    AddPos(300);
}

void PlayerLife::Show(SDL_Renderer* screen)
{   
    for (int i = 0; i < position_list_.size(); i++)
    {
        rect_.x = position_list_.at(i);
        rect_.y = 15;
        Render(screen);
    }
}

void PlayerLife::Decrease()
{
    number_--;
    position_list_.pop_back();
}
*/