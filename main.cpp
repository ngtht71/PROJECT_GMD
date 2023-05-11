#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ExplosionObject.h"
#include "TextObject.h"
//#include "Button.h"
//#include "GameUtils.h"
#include "PlayerLife.h"
#include "Menu.h"

using namespace std;

BaseObject gLoseTexture;
BaseObject gWinTexture;
/*
BaseObject gMenuTexture;
BaseObject gInstructionTexture;
BaseObject gPlayButtonTexture;
BaseObject gHelpButtonTexture;
BaseObject gExitButtonTexture;
BaseObject gBackButtonTexture;
BaseObject gPauseButtonTexture;
BaseObject gContinueButtonTexture;


SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
*/
/*
Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
*/

//The music that will be played
Mix_Music* gMusic = NULL;
//The sound effects that will be used
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gWin = nullptr;
Mix_Chunk* gExplosion = nullptr;


BaseObject g_background;
TTF_Font* g_font = NULL;


bool InitData();
bool LoadBackground();  

bool LoadMedia();

void close();


int main(int argc, char* argv[])
{
    ImpTimer fps;

    //Start up SDL and create window
    InitData();
    LoadBackground();
    LoadMedia();

    if (InitData() == false) return -1;
    if (!LoadBackground()) return -1;
    if (!LoadMedia())   return -1;
     

    bool Play_Again = false;
    Menu menu(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!Play_Again)
    {
        menu.loadMenuIMG(g_screen);
        Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
        while (menu.in_menu) 
        {
            SDL_Delay(10);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    menu.in_menu = false;
                    return 0;
                }
                menu.handleEvent(event);
                if (event.type == SDL_KEYDOWN)
                    Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            }
            menu.render(g_screen);
        }
        
        if (menu.exit_game) Play_Again = false;
        else Play_Again = true;
    }

    int num_die = 0;
    PlayerLife player_life;
    player_life.Init(g_screen);

    //Button pause_button;
    //PlayerLife pause_button;
    //pause_button.InitPause(g_screen);

    SDL_Event e;
     
    //main loop game
    while (Play_Again)
    {
        string highscore = GetHighScoreFromFile("high_score.txt");
        int score = 0;
        int time = 0;

        Mix_PlayMusic(gMusic, IS_REPEATITIVE);

         // load file map
        char dat[100] = "map/map1.dat";
        GameMap game_map;
        game_map.LoadMap(dat);
        game_map.LoadMapTiles(g_screen);

        // load img player
        MainObject p_player;
        p_player.LoadImg(g_name_main, g_screen);
        p_player.set_clips();

        ExplosionObject exp_main;

        bool ret = exp_main.LoadImg("imgs//explosion_11x2.png", g_screen);
        exp_main.set_clips(); 

        if (!ret) return 0;

        Mix_PlayMusic(gMusic, IS_REPEATITIVE);



        TextObject mark_game;
        mark_game.setColor(TextObject::WHITE_TEXT);
        
        TextObject high_score_game;
        high_score_game.setColor(TextObject::WHITE_TEXT);
        

        bool quit = false;
        bool Game_State = true;
        //bool quit = false;
        while (!quit)
        {
            UpdateGameTimeAndScore(time, score);
            if (Game_State)
            {
                
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        Play_Again = false;
                    }
                
                    p_player.HandleInputAction(e, g_screen);
                }


                fps.start();

                while (SDL_PollEvent(&event) != 0)
                {
                    //User requests quit
                    if (event.type == SDL_QUIT) Play_Again = false;
                    p_player.HandleInputAction(event, g_screen);
                }

                SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(g_screen);
                // trước khi load ảnh set lại màu cho màn hình - clear screen

                g_background.Render(g_screen, NULL);

                Map ga_map = game_map.GetMap();

                p_player.SetMapXY(ga_map.start_x_, ga_map.start_y_);
                p_player.DoPlayer(ga_map);
                p_player.Show(g_screen);

                game_map.SetMap(ga_map);
                game_map.DrawMap(g_screen);

                player_life.Show(g_screen);
                //pause_button.Show(g_screen);
                //pause_button.Render(g_screen);


                 // show mark to screen
                string score_val = "Score: ";
                string str_score = to_string(score);
                score_val += str_score;

                mark_game.SetText(score_val);
                mark_game.loadFromRenderedText(g_font, g_screen);
                mark_game.RenderText(g_screen, SCREEN_WIDTH - 300, 15);

                //show high score
                string high_score_val = "High score: ";
                high_score_val += highscore;

                high_score_game.SetText(high_score_val);
                high_score_game.loadFromRenderedText(g_font, g_screen);
                high_score_game.RenderText(g_screen, SCREEN_WIDTH - 300, 45);


                bool win_game = p_player.WinGame(ga_map);
                if (win_game) {
                    cout << "Win game!\n";

                    Mix_PauseMusic();
                    Mix_PlayChannel(-1, gWin, NOT_REPEATITIVE);

                    
                    DrawWinGameSelection(gWinTexture, &e, g_screen, Play_Again);
                    quit = true;
                    Play_Again = false;
                    return 0;
                }

                //dead effect - khi no chet thi cho quit = true
                bool collision = p_player.ColToMap(ga_map);
                if (collision == true)
                {
                    UpdateHighScore("high_score.txt", score, highscore);
                    score = 0;

                    int width_exp_frame = exp_main.get_frame_height();
                    int heiht_exp_height = exp_main.get_frame_width();

                    // chay explosion effect
                    for (int ex = 0; ex < 12; ex++)
                    {
                        int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame / 2;
                        // trừ để tâm vụ nổ vào chính con bị nổ
                        int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - heiht_exp_height / 3;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);


                        Mix_PlayChannel(-1, gExplosion, NOT_REPEATITIVE);   // sound cho va cham no
                        Mix_PauseMusic();               // tam dung nhac
                        Mix_RewindMusic();              // nhac chay lai tu dau
                        exp_main.Free();
                    }

                    num_die++;
                    cout << num_die << endl;
                    if (num_die <= MAX_NUM_DIE)
                    {
                        p_player.set_come_back_time(100);
                        SDL_Delay(150);
                        quit = true;
                        //Play_Again = true;
                        player_life.Decrease();
                        player_life.Render(g_screen);
                        
                    }
                    else
                    {
                        Mix_HaltChannel(-1);
                        Mix_PlayChannel(-1, gLose, NOT_REPEATITIVE);
                        DrawEndGameSelection(gLoseTexture, &e, g_screen, Play_Again, menu.in_menu);
                        quit = true;
                        Play_Again = false;
                        menu.in_menu = true;
                        //return 0;
                    }
                }

                SDL_RenderPresent(g_screen);

                int imp_time = fps.get_ticks();
                int time_for_one_frame = 1000 / FRAMES_PER_SECOND;

                if (imp_time < time_for_one_frame) {

                    int delay_time = time_for_one_frame - imp_time;
                    SDL_Delay(delay_time);
                }

            }
            //SDL_RenderPresent(g_screen);
            //else Play_Again = false;
        }
    }
    close();
    return 0;
}

// test mixer and ttf
bool LoadMedia()
{
    bool success = true;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        return false;

    gMusic = Mix_LoadMUS("sound/BackOnTrack.wav");
    if (gMusic == nullptr)
    {
        LogError("Failed to load background music", MIX_ERROR);
        success = false;
    }
   
    gMenuMusic = Mix_LoadMUS("sound/Machina.wav");
    if (gMenuMusic == nullptr)
    {
        LogError("Failed to load menu music", MIX_ERROR);
        success = false;
    }
    

    gClick = Mix_LoadWAV("sound//mouse_click.wav");
    if (gClick == nullptr)
    {
        LogError("Failed to load mouse click sound", MIX_ERROR);
        success = false;
    }

    
    gExplosion = Mix_LoadWAV("sound/Fire1.wav");
    if (gExplosion == nullptr)
    {
        LogError("Failed to load explosion sound ", MIX_ERROR);
        success = false;
    }

    gLose = Mix_LoadWAV("sound/lose_sound.wav");
    if (gLose == nullptr)
    {
        LogError("Failed to load lose sound", MIX_ERROR);
        success = false;
    }
    
    gWin = Mix_LoadWAV("sound/win.wav");
    if (gWin == nullptr)
    {
        LogError("Failed to load win sound", MIX_ERROR);
        success = false;
    }
    if (!gLoseTexture.LoadImg("menu/lose.png", g_screen))
    {
        cout << "Failed to load lose image." << endl;
        success = false;
    }
    if (!gWinTexture.LoadImg("menu/win.png", g_screen))
    {
        cout << "Failed to load win image.\n";
        success = false;
    }
    return success;
    
}

bool LoadBackground()
{
    bool success = true;
    
    //if (!g_background.LoadImg("imgs//bg.jpg", g_screen)) {
    if (!g_background.LoadImg("imgs/game1.jpg", g_screen))    //imgs//background.jpg
    {
        cout << "Failed to load background texture!\n";
        success = false;
    }
    return success;
}
    

bool InitData()
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_VIDEO); 

    if (ret < 0) return false;                                   // hàm chạy có lỗi

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");             //Thành công thì set render tỉ lệ chất lượng

    //Create window
    g_window = SDL_CreateWindow("GEOMETRY DASH", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == NULL) success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;

            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        // font mark
        if (TTF_Init() == -1) success = false;

        g_font = TTF_OpenFont("font//gooddog.ttf", 35);         // 35 la == size text
        if (g_font == NULL) return false;


    }
        return success;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    Mix_FreeMusic(gMusic);
    Mix_FreeMusic(gMenuMusic);
    Mix_FreeChunk(gClick);
    Mix_FreeChunk(gLose);
    Mix_FreeChunk(gWin);
    gMusic = nullptr;
    gMenuMusic = nullptr;
    gClick = nullptr;
    gLose = nullptr;
    gWin = nullptr;

    gWinTexture.Free();
    gLoseTexture.Free();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

