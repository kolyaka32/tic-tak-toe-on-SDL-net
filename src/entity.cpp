#include "include.hpp"
#include "SDL_net.h"
#include "structs.hpp"

#include "dataLoader.hpp"


Field::Field(/* args */)
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

    //Checking for win
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

// Return 0, if none win, 1, if win player, 2 if win bot(2 player)
int Field::checkWin(coord X, coord Y){
    Uint8 state = data[Y * fieldWidth];
    for(coord x = 1; x < fieldWidth; ++x){
        state &= data[Y * fieldWidth + x];
    }
    if(state){
        return state;
    }

    state = data[X];
    for(coord y = 1; y < fieldWidth; ++y){
        state &= data[y * fieldWidth + X];
    }
    if(state){
        return state;
    }

    // Checking diagonal
    if(X == Y){
        state = data[0];
        for(coord t = 1; t < fieldWidth; ++t){
            state &= data[(fieldWidth + 1) * t];
        }
        if(state){
            return state;
        }
    }
    else if(fieldWidth - 1 == X + Y){
        state = data[fieldWidth - 1];
        for(coord t = fieldWidth; t > 1; --t){
            state &= data[(fieldWidth - 1) * t];
        }
        if(state){
            return state;
        }
    }
    bool c = true;
    for(coord t=0; t < fieldWidth * fieldWidth; ++t){
        if(!data[t]){
            c = false;
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