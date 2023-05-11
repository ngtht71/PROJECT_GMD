#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
}


ExplosionObject::~ExplosionObject()
{
}

bool ExplosionObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        frame_width_ = rect_.w / NUM_FRAME_EXP;
        frame_height_ = rect_.h;
    }

    return ret;
}

void ExplosionObject::set_clips()
{
    //Clip the sprites
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = frame_width_;
        frame_clip_[0].h = frame_height_;

        frame_clip_[1].x = frame_width_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = frame_width_;
        frame_clip_[1].h = frame_height_;

        frame_clip_[2].x = frame_width_ * 2;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = frame_width_;
        frame_clip_[2].h = frame_height_;

        frame_clip_[3].x = frame_width_ * 3;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = frame_width_;
        frame_clip_[3].h = frame_height_;

        frame_clip_[4].x = frame_width_ * 4;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = frame_width_;
        frame_clip_[4].h = frame_height_;

        frame_clip_[5].x = frame_width_ * 5;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = frame_width_;
        frame_clip_[5].h = frame_height_;

        frame_clip_[6].x = frame_width_ * 6;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = frame_width_;
        frame_clip_[6].h = frame_height_;

        frame_clip_[7].x = frame_width_ * 7;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = frame_width_;
        frame_clip_[7].h = frame_height_;

        frame_clip_[8].x = frame_width_ * 8;
        frame_clip_[8].y = 0;
        frame_clip_[8].w = frame_width_;
        frame_clip_[8].h = frame_height_;

        frame_clip_[9].x = frame_width_ * 9;
        frame_clip_[9].y = 0;
        frame_clip_[9].w = frame_width_;
        frame_clip_[9].h = frame_height_;

        frame_clip_[10].x = frame_width_ * 10;
        frame_clip_[10].y = 0;
        frame_clip_[10].w = frame_width_;
        frame_clip_[10].h = frame_height_;

        frame_clip_[11].x = frame_width_ * 11;
        frame_clip_[11].y = 0;
        frame_clip_[11].w = frame_width_;
        frame_clip_[11].h = frame_height_;
    }
}

void ExplosionObject::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = { rect_.x, rect_.y, frame_width_, frame_height_ };
    if (currentClip != NULL)
    {
        renderQuad.w = currentClip->w;
        renderQuad.h = currentClip->h;
    }

    SDL_RenderCopy(screen, p_object_, currentClip, &renderQuad);
}