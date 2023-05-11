#pragma once
#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
//#include "ExplosionObject.h"

using namespace std;

#define GRAVITY_SPEED 1.5    // tốc độ rơi sau khi nhảy
#define MAX_FALL_SPEED 18 // tốc độ rơi tối đa

#define PLAYER_SPEED 8
#define PLAYER_HIGHT_VAL 21  //tốc độ di chuyển của player

#define NUM_FRAME 8
#define TRIANGLE 2
#define RECTANGLE 3
#define HALF_RECTANGLE 6
#define DOUBLE_TRIANGLE 5
#define TRIANGLE_DOWN 4
#define TRIANGLE_LEFT 7
#define TRIANGLE_RIGHT 8
#define WALL_UP 13
#define WALL_DOWN 14
#define GOAL 16

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
    };

    void set_clips();
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x, map_y_ = map_y; };

    void DoPlayer(Map& g_map);

    void CenterEntityOnMap(Map& g_map);
    void CheckToMap(Map& g_map);

    int get_frame_width() const { return width_frame_; }
    int get_frame_height() const { return height_frame_; }
    void set_come_back_time(const int& come_back_time_) { come_back_time = come_back_time_; }

    bool ColToMap(Map& g_map);

    bool WinGame(Map& g_map);

    SDL_Rect GetRectFrame();

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    //khởi tạo map_x_ = map_y_ = 0 lưu vị trí bản đồ của hàm SetMapXY
    int map_x_;
    int map_y_;

    bool is_jump_;
    bool on_ground_;
    int come_back_time; 

    // kích thước của 1 frame (thường cd có 8 frame)
    int width_frame_;
    int height_frame_;

    // hàm lưu 8 frame
    SDL_Rect frame_clip_[8];

    Input input_type_;    // lưu trạng thái di chuyển
    int frame_;          // đang ở frame mấy 
    int status_;            // trạng thái di chuyển phải trái..

};

#endif