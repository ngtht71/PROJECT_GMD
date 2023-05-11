#include "PlayerLife.h"

PlayerLife::PlayerLife() { number_ = 0; }
PlayerLife::~PlayerLife(void) {}

void PlayerLife::AddPos(const int& xPos) { position_list_.push_back(xPos); }

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

void PlayerLife::InitPause(SDL_Renderer* screen)
{
    LoadImg("imgs//pause.png", screen);
    number_ = 1;

    if (position_list_.size() > 0)
        position_list_.clear();

    AddPos(500);
    
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