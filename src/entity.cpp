#include "include.hpp"
#include "SDL_net.h"
#include "structs.hpp"

#include "dataLoader.hpp"


Field::Field()
{
    data = (Uint8*)malloc(sizeof(Uint8) * fieldWidth * fieldWidth);
    reset();
}

Field::~Field()
{
    free(data);
}

void Field::reset(){
    for(Uint8 i=0; i < fieldWidth * fieldWidth; ++i){
        data[i] = CELL_EMPTY;
    }
}

void Field::clickSingle(coord x, coord y){
    // Checking, if cell empty
    if(data[x + y * fieldWidth] == CELL_EMPTY){
        data[x + y * fieldWidth] = CELL_MY;

        //Checking for win
        switch (checkWin(x, y))
        {
        case CELL_MY:
            winning = true;
            break;
        
        case CELL_ENEMY:
            loosing = true;
            break;
        case 3:
            nobody = true;
            break;
        }
        AImove();
    }
}

void Field::clickTwo(coord x, coord y){
    // Checking, if cell empty
    if(data[x + y * fieldWidth] == CELL_EMPTY){
        data[x + y * fieldWidth] = CELL_MY + player;

        player = (player+1)%2;  // Changing player

        //Checking for win
        switch (checkWin(x, y))
        {
        case CELL_MY:
            winning = true;
            break;
        
        case CELL_ENEMY:
            loosing = true;
            break;

        case 3:
            nobody = true;
            break;
        }
    }
}

void Field::clickMulti(coord x, coord y, TCPsocket sendPlace){
    // Checking, if cell empty
    if(data[x + y * fieldWidth] == CELL_EMPTY){
        data[x + y * fieldWidth] = CELL_MY + player;

        // Sending data to another player
        Uint8 sendData[5] = {3, x, y, player, 0};
        SDLNet_TCP_Send(sendPlace, sendData, 5);

        player = (player + 1) % 2;  // Changing player

        //Checking for win
        switch (checkWin(x, y))
        {
        case CELL_MY:
            winning = true;
            break;
        
        case CELL_ENEMY:
            loosing = true;
            break;

        case 3:
            nobody = true;
            break;
        }
    }
}

// Recursivly solve, where cell need to be placed
Sint8 Field::recSolve(Uint8 round){
    // Look for best place to set
    Sint8 result = 0;
    for(coord y=0; y < fieldWidth; ++y)
        for(coord x=0; x < fieldWidth; ++x){
            if(data[y * fieldWidth + x] == CELL_EMPTY){
                // Trying set cell and think, what happen next
                data[y * fieldWidth + x] = (round % 2) + 1;  // Set player cell on odd rounds and enemy cell in even
                switch (checkWin(x, y))
                {
                case CELL_MY:
                    if(round % 2){
                        result--;
                    }
                    else{
                        result++;
                    }
                    break;
                
                case CELL_ENEMY:
                    if(round % 2){
                        result++;
                    }
                    else{
                        result--;
                    }
                    break;
                case 3:  // If field already filled
                    break;
                default:
                    result -= recSolve(round+1);
                };
                data[y * fieldWidth + x] = CELL_EMPTY;
            }
    }
    return result;
}

void Field::AImove(){
    Sint8 maxScore = -127;
    coord maxPos = 0;

    // Finding best place for move
    for(coord i=0; i < fieldWidth * fieldWidth; ++i){
        if(data[i] == CELL_EMPTY){
            data[i] = CELL_ENEMY;
            Sint8 cur = recSolve(1);
            if(cur > maxScore){
                maxScore = cur;
                maxPos = i;
            }
            data[i] = CELL_EMPTY;
        }
    }
    //
    data[maxPos] = CELL_ENEMY;

    // Checking for win
    switch (checkWin(maxPos % fieldWidth, maxPos / fieldWidth))
    {
    case CELL_MY:
        winning = true;
        break;
    
    case CELL_ENEMY:
        loosing = true;
        break;
    case 3:
        nobody = true;
        break;
    }
}

// New checkWin function 
// Return 0, if none win, 1, if win player, 2 if win bot(2 player)
Uint8 Field::checkWin(const coord X, const coord Y){
    // Flag, which save type for control win
    Uint8 state;
    // Finding first starting point for X
    for(Uint8 startX = MAX(0, X - winWidth + 1); startX <= MIN(X, fieldWidth - winWidth); ++startX){
        // Checking all line
        state = CELL_MY | CELL_ENEMY;

        for(coord x = startX; (x < startX + winWidth) && state; ++x){
            state &= data[Y * fieldWidth + x];
        }

        if(state){
            return state;
        }
    }

    // Finding same first starting point for Y
    for(Uint8 startY = MAX(0, Y - winWidth + 1); startY <= MIN(Y, fieldWidth - winWidth); ++startY){
        // Checking all collumn
        state = CELL_MY | CELL_ENEMY;

        for(coord y = startY; (y < startY + winWidth) && state; ++y){
            state &= data[y * fieldWidth + X];
        }

        if(state){
            return state;
        }
    }

    // Checking primal diagonal
    for(Uint8 startT = MAX(X - Y, 0); startT <= MIN(fieldWidth - winWidth, fieldWidth + X - Y - winWidth); ++startT){
        state = CELL_MY | CELL_ENEMY;

        for(Uint8 t = startT; (t < winWidth + startT) && state; ++t){
            state &= data[t + (Y + t - X) * fieldWidth];
        }
        if(state){
            return state;
        }
    }

    // Checking second diagonal
    for(Sint8 startT = MIN(X + Y, fieldWidth); startT+1 > MIN(winWidth, winWidth - X - Y); --startT){
        state = CELL_MY | CELL_ENEMY;

        for(Sint8 t = startT; (t > startT - winWidth); --t){
            state &= data[X + Y + t * (fieldWidth-1)];
        }
        if(state){
            return state;
        }
    }

    // Checking, is field full
    bool c = true;
    for(coord t=0; t < fieldWidth * fieldWidth; ++t){
        if(data[t] == CELL_EMPTY){
            c = false;
            break;
        }
    }
    if(c){
        return 3;
    }
    return 0;
}

void Field::blit(){
    // Rendering cells with their background
    for(coord y=0; y < fieldWidth; ++y)
        for(coord x=0; x <fieldWidth; ++x){
            SDL_Rect dest = {x * (CELL_SIDE + SEPARATOR), y * (CELL_SIDE + SEPARATOR), CELL_SIDE, CELL_SIDE};
            // Rendering background
            SDL_RenderCopy(app.renderer, Textures[IMG_CELL], NULL, &dest);
            
            // Rendering cells
            switch (data[y * fieldWidth + x])
            {
            case CELL_MY:
                SDL_RenderCopy(app.renderer, Textures[IMG_GREEN_CROSS + queue], NULL, &dest);
                break;

            case CELL_ENEMY:
                SDL_RenderCopy(app.renderer, Textures[IMG_RED_CIRCLE - queue], NULL, &dest);
                break;
            }
        }
}