#include "Menu.h"

using namespace std;

Menu::Menu(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    screenW = SCREEN_WIDTH;
    screenH = SCREEN_HEIGHT;

    optionsNumber = 1;
    optionChoosen = 0;

    transVelo = 0;

    blinkTimes = 0;

    in_menu = true;
    doneTransition = true;
    menuToInstruction = false;

    exit_game = false;
    frameTime = SDL_GetTicks();
}

Menu :: ~Menu()
{
}

void Menu::loadMenuIMG(SDL_Renderer* renderer)
{
    menuTexture = BaseObject::loadTexture("menu/menu.png", renderer);

    play = BaseObject::loadTexture("menu/play.png", renderer);
    playChoosen = BaseObject::loadTexture("menu/play1.png", renderer);
    playPos.w = COMMON_BUTTON_WIDTH * 1.2;
    playPos.x = PLAY_BUTTON_POSX - 40 ;
    playPos.h = COMMON_BUTTON_HEIGHT * 1.2;
    playPos.y = PLAY_BUTTON_POSY - 20;

    exit = BaseObject::loadTexture("menu/exit.png", renderer);
    exitChoosen = BaseObject::loadTexture("menu/exit1.png", renderer);
    exitPos.w = SECOND_BUTTON_WIDTH * 1.2;
    exitPos.x = EXIT_BUTTON_POSX -40;
    exitPos.h = SECOND_BUTTON_HEIGHT * 1.2;
    exitPos.y = EXIT_BUTTON_POSY -20;

    instruction = BaseObject::loadTexture("menu/help.png", renderer);
    instructionChoosen = BaseObject::loadTexture("menu/help1.png", renderer);
    instructionPos.w = SECOND_BUTTON_WIDTH * 1.2;
    instructionPos.x = HELP_BUTTON_POSX - 40;
    instructionPos.h = SECOND_BUTTON_HEIGHT * 1.2 ;
    instructionPos.y = HELP_BUTTON_POSY -20;

    ins1 = BaseObject::loadTexture("menu/ins1.png", renderer);
    ins1Pos.w = 900;
    ins1Pos.x = screenW ;
    ins1Pos.h = 450;
    ins1Pos.y = screenH / 4 - 50 ;

    ins2 = BaseObject::loadTexture("menu/ins2.png", renderer);
    ins2Pos.w = 900;
    ins2Pos.x = ins1Pos.x + ins1Pos.w + 250;
    ins2Pos.h = 450;
    ins2Pos.y = screenH / 4 - 50;

    Right = BaseObject::loadTexture("menu/right.png", renderer);
    RightPos.w = 100;
    RightPos.x = instructionPos.x - 75;
    RightPos.h = 125;
    RightPos.y = playPos.y + 50;

    Left = BaseObject::loadTexture("menu/left.png", renderer);
    LeftPos = RightPos;
    LeftPos.x = instructionPos.x + instructionPos.w + 20;

    Return = BaseObject::loadTexture("menu/Return.png", renderer);
    ReturnPos.w = 600;
    ReturnPos.x = (screenW - ReturnPos.w) / 2;
    ReturnPos.h = 30;
    ReturnPos.y = screenH - ReturnPos.h - 20;

    SDL_QueryTexture(Return, NULL, NULL, &ReturnRect.w, &ReturnRect.h);
    ReturnRect.h /= 2;
    ReturnRect.x = ReturnRect.y = 0;

    buttonInstruction = BaseObject::loadTexture("menu/button.png", renderer);
    buttonInstructionPos.w = 700;
    buttonInstructionPos.x = (screenW - buttonInstructionPos.w) / 2;
    buttonInstructionPos.h = 50;
    buttonInstructionPos.y = screenH - buttonInstructionPos.h - 20;

    SDL_QueryTexture(buttonInstruction, NULL, NULL, &buttonInstructionRect.w, &buttonInstructionRect.h);
    buttonInstructionRect.h /= 2;
    buttonInstructionRect.x = buttonInstructionRect.y = 0;
}

void Menu::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //ngoai menu->chon play
        if (optionChoosen == 0) {
            if (optionsNumber == 1 && e.key.keysym.sym == SDLK_LEFT) {
                //RightPos.y = LeftPos.y = instructionPos.y - 5;
                optionsNumber = 2;
            }

            if (optionsNumber == 1 && e.key.keysym.sym == SDLK_RIGHT)
                optionsNumber = 3;

            if (optionsNumber == 2 && e.key.keysym.sym == SDLK_RIGHT)
                optionsNumber = 1;

            if (optionsNumber == 3 && e.key.keysym.sym == SDLK_LEFT)
                optionsNumber = 1;

            if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) {
                optionChoosen = optionsNumber;
                if (optionChoosen == 1) blinkingTime = SDL_GetTicks();
                else if (optionChoosen == 2) {
                    menuToInstruction = true;
                    RightPos.x = screenW;
                    LeftPos.x = -LeftPos.w;
                }
                else if (optionChoosen == 3)
                {
                    in_menu = false;
                    exit_game = true;
                }
            }
        }
        // chon instruction
        else if (optionChoosen == 2) {
            if (doneTransition) {
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    transVelo = -20;
                    doneTransition = false;
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    transVelo = 20;
                    doneTransition = false;
                }
            }
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                optionChoosen = 0;
                //instructionPos.y = playPos.y + 2 * playPos.h;
                instructionPos.y = HELP_BUTTON_POSY;
                ins1Pos.x = screenW;
                ins2Pos.x = ins1Pos.x + ins1Pos.w + 50;
            }
        }
    }
}

void Menu::render(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

    if (optionChoosen == 0) 
    {
        if (optionsNumber == 1) {
            SDL_RenderCopy(renderer, playChoosen, NULL, &playPos);
            SDL_RenderCopy(renderer, instruction, NULL, &instructionPos);

            SDL_RenderCopy(renderer, exit, NULL, &exitPos);
        }
        else if (optionsNumber == 2) {
            SDL_RenderCopy(renderer, play, NULL, &playPos);
            SDL_RenderCopy(renderer, instructionChoosen, NULL, &instructionPos);

            SDL_RenderCopy(renderer, exit, NULL, &exitPos);
        }
        
        else if (optionsNumber == 3)
        {
            SDL_RenderCopy(renderer, exitChoosen, NULL, &exitPos);
            SDL_RenderCopy(renderer, play, NULL, &playPos);
            SDL_RenderCopy(renderer, instruction, NULL, &instructionPos);
        }
        SDL_RenderCopy(renderer, buttonInstruction, &buttonInstructionRect, &buttonInstructionPos);
        if (SDL_GetTicks() - frameTime >= 500) {
            buttonInstructionRect.y += buttonInstructionRect.h;
            frameTime = SDL_GetTicks();
        }
        if (buttonInstructionRect.y >= 2 * buttonInstructionRect.h) buttonInstructionRect.y = 0;
    }
    if (optionChoosen == 2) 
    {
        if (ins1Pos.x > 130 && menuToInstruction) {
            ins1Pos.x -= 40;
            ins2Pos.x -= 40;
            if (ins1Pos.x <= 130) {
                RightPos.x = screenW - RightPos.w - 50;
            }
        }

        if (ins1Pos.x < 130) menuToInstruction = false;

        if (transVelo > 0) {
            if (ins1Pos.x < 130) {
                ins1Pos.x += transVelo;
                ins2Pos.x += transVelo;
            }
            else if (ins1Pos.x >= 130) {
                transVelo = 0;
                doneTransition = true;
                RightPos.x = screenW - RightPos.w - 50;
                LeftPos.x = -LeftPos.w;
            }
        }
        else if (transVelo < 0) {
            if (ins2Pos.x > 130) {
                ins1Pos.x += transVelo;
                ins2Pos.x += transVelo;
            }
            else if (ins2Pos.x <= 130) {
                transVelo = 0;
                doneTransition = true;
                RightPos.x = screenW;
                LeftPos.x = 50;
            }
        }
        SDL_RenderCopy(renderer, ins1, NULL, &ins1Pos);
        SDL_RenderCopy(renderer, ins2, NULL, &ins2Pos);

        SDL_RenderCopy(renderer, Left, NULL, &LeftPos);
        SDL_RenderCopy(renderer, Right, NULL, &RightPos);

        SDL_RenderCopy(renderer, Return, &ReturnRect, &ReturnPos);
        if (SDL_GetTicks() - frameTime >= 500) {
            ReturnRect.y += ReturnRect.h;
            frameTime = SDL_GetTicks();
        }
        if (ReturnRect.y >= 2 * ReturnRect.h) ReturnRect.y = 0;
    }
    SDL_RenderPresent(renderer);
    if (optionChoosen == 1 && blinkTimes < 3 && SDL_GetTicks() - blinkingTime >= 100) {
        Mix_HaltMusic();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        blinkingTime = SDL_GetTicks();
        blinkTimes++;
    }
    if (blinkTimes >= 3) {
        in_menu = false;
        SDL_Delay(1000);
    }
}


void DrawEndGameSelection(BaseObject gLoseTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again, bool& in_menu)
{
    //gLoseTexture.Free();
    if (Play_Again)
    {
        bool End_Game = false;
        while (!End_Game)
        {
            while (SDL_PollEvent(e) != 0)
            {
                if (e->type == SDL_QUIT)
                {
                    Play_Again = false;
                    End_Game = true;
                }

                if (e->type == SDL_KEYDOWN)
                {
                    End_Game = true;
                    Play_Again = false;
                }
            }

            gLoseTexture.Render(gRenderer, NULL);

            SDL_RenderPresent(gRenderer);
            gLoseTexture.Free();
        }
    }

}

void DrawWinGameSelection(BaseObject gWinTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again)
{
    //gWinTexture.Free();
    if (Play_Again)
    {
        bool End_Game = false;
        while (!End_Game)
        {
            while (SDL_PollEvent(e) != 0)
            {
                if (e->type == SDL_QUIT) Play_Again = false;

                if (e->type == SDL_KEYDOWN)
                {
                    End_Game = true;
                    Play_Again = false;
                }
            }
        }
    }

}