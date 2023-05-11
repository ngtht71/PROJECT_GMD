
#include "MainObject.h"


MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 500;
	x_val_ = 0;
	y_val_ = 0;
	
	width_frame_ = 0;
	height_frame_ = 0;

    status_ = -1;

	map_x_ = 0;
	map_y_ = 0;

	on_ground_ = false;
    come_back_time = 0;

	input_type_.right_ = 1;
	input_type_.jump_ = 0;

	status_ = WALK_NONE;
}

MainObject::~MainObject()
{
	Free();
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = rect_.w / NUM_FRAME;   // = width_frame_
    rect.h = rect_.h;
    return rect;
}

//check neu va cham thi cho chay explosion effect
bool MainObject::ColToMap(Map& g_map)
{
    // ret luu xem co va cham voi map khong
    bool ret = false;
    
    // giới hạn kiểm tra theo chiều x từ x1-x2
    int x1 = 0;
    int x2 = 0;

    //giới hạn kiểm tra theo chiều y từ y1-y2
    int y1 = 0;
    int y2 = 0;

    //Check Horizontal - ngang
    int height_min = (height_frame_ < TILE_SIZE) ? height_frame_ : TILE_SIZE;

    // tìm ra ô đứng hiện tại
    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    int val1 = g_map.tile[y1][x2];
    int val2 = g_map.tile[y2][x2];
    // Check current position of map. It is not blank_tile.
    if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE)) ret = true;



    // Check vertical
    int width_min = (width_frame_ < TILE_SIZE) ? width_frame_ : TILE_SIZE;

    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    int val3 = g_map.tile[y2][x1];
    int val4 = g_map.tile[y2][x2];

    if (val3 == TRIANGLE || val4 == TRIANGLE) ret = true;
    else if (val3 == DOUBLE_TRIANGLE || val4 == DOUBLE_TRIANGLE) ret = true;
    else if (val3 == TRIANGLE_DOWN || val4 == TRIANGLE_DOWN) ret = true;
    else if (val3 == TRIANGLE_LEFT || val4 == TRIANGLE_LEFT) ret = true;
    else if (val3 == TRIANGLE_RIGHT || val4 == TRIANGLE_RIGHT) ret = true;
    else if (val3 == WALL_UP || val4 == WALL_UP) ret = true;
    else if (val3 == WALL_DOWN || val4 == WALL_DOWN) ret = true;

    return ret;

}

void MainObject::CheckToMap(Map& g_map)
{
    // giới hạn kiểm tra theo chiều x từ x1-x2
    int x1 = 0;
    int x2 = 0;

    //giới hạn kiểm tra theo chiều y từ y1-y2
    int y1 = 0;
    int y2 = 0;

    //Check Horizontal - ngang
    int height_min = (height_frame_ < TILE_SIZE) ? height_frame_ : TILE_SIZE;    

    // tìm ra ô đứng hiện tại
    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    // Check x1, x2 with full width of map
    // Check y1, y2 with full heigth of map
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // when object is moving by right  ===>
        {
            int val1 = g_map.tile[y1][x2];
            int val2 = g_map.tile[y2][x2];
           
            if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE)) 
            {
                // Fixed post of object at current post of map.
                // => Cannot moving when press button
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0; // cannot moving                
            }
        }
    }

  // Check vertical
  int width_min = (width_frame_ < TILE_SIZE) ? width_frame_ : TILE_SIZE;

  x1 = (x_pos_) / TILE_SIZE;
  x2 = (x_pos_ + width_min) / TILE_SIZE;

  y1 = (y_pos_ + y_val_) / TILE_SIZE;
  y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {

      // trạng thái rơi từ trên xuống
      if (y_val_ > 0)
      {
          //Similar for vertical
          int val1 = g_map.tile[y2][x1];
          int val2 = g_map.tile[y2][x2];

          if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
          {
              y_pos_ = y2 * TILE_SIZE;
              y_pos_ -= height_frame_;

              y_val_ = 0;

              on_ground_ = true;
              if (status_ == WALK_NONE) status_ = WALK_RIGHT;
          }
      }
      else if (y_val_ < 0)
      {
          int val1 = g_map.tile[y1][x1];
          int val2 = g_map.tile[y1][x2];
          if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
          {
             y_pos_ = (y1 + 1) * TILE_SIZE;

             y_val_ = 0;
          }
      }
  }
      //If there is not collision with map tile - nếu k va chạm với map   

  x_pos_ += x_val_;
  y_pos_ += y_val_;

  if (x_pos_ < 0)  x_pos_ = 0;
  else if (x_pos_ + width_frame_ >= g_map.max_x_)   // x2 > rộng map
     x_pos_ = g_map.max_x_ - width_frame_ - 1;

}

bool MainObject::LoadImg(string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / NUM_FRAME;
		height_frame_ = rect_.h;
	}
	return ret;
}

void MainObject::set_clips()
{
    //Clip the sprites
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = width_frame_ * 2;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = width_frame_ * 3;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = width_frame_ * 4;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = width_frame_ * 5;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = width_frame_ * 6;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = width_frame_ * 7;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;
    }
}

bool MainObject::WinGame(Map& g_map)
{
    bool win_game = false;
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min = (height_frame_ < TILE_SIZE) ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        int val1 = g_map.tile[y1][x2];
        int val2 = g_map.tile[y2][x2];

        if ((val1 == GOAL) || (val2 == GOAL))
            win_game = true;
    }

    return win_game;
}

void MainObject::Show(SDL_Renderer* des)
{
    LoadImg("imgs//player.png", des);
    
    if (input_type_.right_ == 1) frame_++;
    else frame_ = 0;

    if (frame_ >= 8) frame_ = 0;
    
    // sau khi viết cho map di chuyển theo player
    if (come_back_time == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        // phải trừ đi phần map_x_ mà bản đồ di chuyển 

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
    
        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
    }
}

//hàm xử lý sự kiện
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen) 
{

  //If a key was pressed
  if( events.type == SDL_KEYDOWN )
  {
      //Set the velocity
      if (events.key.keysym.sym == SDLK_SPACE)
          input_type_.jump_ = 1;
  }
 
  // xử lý nhảy cho nhân vật
  else if (events.type == SDL_MOUSEBUTTONDOWN)
  {
      if (events.button.button == SDL_BUTTON_RIGHT)
          input_type_.jump_ = 1;
  }
}

void MainObject::DoPlayer(Map& g_map)
{
    if (come_back_time == 0)
    {
        x_val_ = 0;

        y_val_ += GRAVITY_SPEED;

        if (y_val_ >= MAX_FALL_SPEED) y_val_ = MAX_FALL_SPEED;

        if (input_type_.right_ == 1) x_val_ += PLAYER_SPEED;
        
        if (input_type_.jump_ == 1)
        {
            if (on_ground_ == true)
            {
                y_val_ = -PLAYER_HIGHT_VAL;
                
            }

            on_ground_ = false;
            input_type_.jump_ = 0;
        }
        /*
        if (on_ground_ == false)
        {
            x_val_ = PLAYER_SPEED * 2;
        }
        else if (on_ground_ == true)
        {
            x_val_ = PLAYER_SPEED ;
        }
        */
        CheckToMap(g_map);

        CenterEntityOnMap(g_map);
    }
}

// di chuyển map theo player
void MainObject::CenterEntityOnMap(Map& g_map)
{
    g_map.start_x_ = x_pos_ - (1.0*SCREEN_WIDTH / 2);
    // khi player đi đến giữa màn hình

    if (g_map.start_x_ < 0) g_map.start_x_ = 0;
    // khi nhân vật lùi thì map k lùi

    else if (g_map.start_x_ + SCREEN_WIDTH >= g_map.max_x_) g_map.start_x_ = g_map.max_x_ - SCREEN_WIDTH;

    g_map.start_y_ = y_pos_ - (1.0*SCREEN_HEIGHT / 2);

    if (g_map.start_y_ < 0) g_map.start_y_ = 0;

    else if (g_map.start_y_ + SCREEN_HEIGHT >= g_map.max_y_) g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
}
