#include "ImpTimer.h"
#include "CommonFunc.h"

ImpTimer::ImpTimer()
{
    start_tick_ = 0;
    paused_ticks_ = 0;
    is_paused_ = false;
    is_started_ = false;
}

//ImpTimer::~ImpTimer() { ; }

void ImpTimer::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
    // liên tục lấy thgian đã trôi qua
}

int ImpTimer::get_ticks()
{
    if (is_started_ == true)
    {
        //If the timer is paused
        if (is_paused_ == true) return paused_ticks_;

        else return SDL_GetTicks() - start_tick_;
    }

    //If the timer isn't running
    return 0;
}
