#include "include.hpp"
#include <string.h>
#include "define.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"
#include "baseGUI.hpp"
#include "pause.hpp"

#define BUFFER_LENGTH 100

using namespace GUI;

// Function of creating font with need height
inline TTF_Font* createFont(Uint8 size){
    SDL_RWops* fontData = SDL_RWFromMem(fontMemory, fontSize);
    return TTF_OpenFontRW(fontData, 1, size);
};


// Class of static text
staticText::staticText(char* newText, Uint8 size, float x, float y, ALIGNMENT_types newAligment, SDL_Color newColor){
    fontHeight = size;
    text = newText;
    posX = x;
    posY = y;
    aligment = newAligment;
    color = newColor;
};

inline void writeNumber(char* buffer, int number, Uint8* pos){
    if(number < 0){
        buffer[*pos++] = '-';
        number = -number;
    }
    Uint8 end = 0;
    int num = number;
    do{
        num /= 10;
        end++;
    } while(num);
    *pos += end;
    do {   
        buffer[--*pos] = '0' + number % 10;
        number /= 10;
    } while (number);
    *pos += end;
}

void staticText::init(){
    Font = createFont(fontHeight);
}

void staticText::updateText(LNG_types language, int number){
    char buffer[BUFFER_LENGTH];
    Uint8 start = 0;
    for(Uint8 end = 0; (end != language) && (start < BUFFER_LENGTH); ++start){
        if(text[start] == '\n'){
            end++;
        }
    }
    Uint8 d = 0;
    for(int i = start; text[i] && (text[i] != '\n') && (start < BUFFER_LENGTH); ++i ){
        switch (text[i])
        {
        case '%':
            writeNumber(buffer, number, &d);
            break;
        
        default:
            buffer[d++] = text[i];
            break;
        }
    }
    buffer[d] = '\0';
    
    SDL_Surface* Surface = TTF_RenderUTF8_Solid(Font, buffer, color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_FreeSurface(Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = (SCREEN_WIDTH) * posX - (Rect.w * aligment / 2); 
    Rect.y = SCREEN_HEIGHT * posY - Rect.h/2;
};

void staticText::blit(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

void staticText::free(){
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
};


// Slider class
Slider::Slider(const float Y, const IMG_names lineImage, const IMG_names buttonImage){
    textureLine = Textures[lineImage];
    textureButton = Textures[buttonImage];
    SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    destLine.x = SCREEN_WIDTH/2-destLine.w/2; 
    destLine.y = SCREEN_HEIGHT * Y - destLine.h / 2; 
    destButton.y = SCREEN_HEIGHT * Y - destButton.h / 2;
};

void Slider::blit(Uint8 state){
    destButton.x = destLine.x + state - destButton.w/2;
    SDL_RenderCopy(app.renderer, textureLine, NULL, &destLine);
    SDL_RenderCopy(app.renderer, textureButton, NULL, &destButton);
};

bool Slider::in(int X, int Y){
    return ((X > destLine.x && X < destLine.x + destLine.w) &&
        (Y > destLine.y && Y < destLine.y+destLine.h));
};

int Slider::getX(){
    return destLine.x;
};


// Button class
Button::Button(const float X, const float Y, const IMG_names newIndex, staticText* top){
    posX = X;
    posY = Y;
    textureIndex = newIndex;
    topText = top;
};

void Button::init(){
    texture = Textures[textureIndex];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = SCREEN_WIDTH * posX - dest.w / 2; 
    dest.y = SCREEN_HEIGHT * posY - dest.h / 2;
};

void Button::blit(){
    SDL_RenderCopy(app.renderer, Textures[textureIndex], NULL, &dest);
    if(topText != nullptr){
        topText->blit();
    }
};

bool Button::in(int x, int y){
    return ((x > dest.x && x < dest.x + dest.w) &&
        (y > dest.y && y < dest.y + dest.h));
};


#if ANI_count
// GIF animation class
Animation::Animation( SDL_Rect destination, ANI_names newType ){
    // Creating animation
    type = newType;
    dest = destination;
    frame = 0; 
    prevTick = 0;
};

void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(app.renderer, Animations[type]->frames[frame]);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    if(SDL_GetTicks64() > prevTick + Animations[type]->delays[0]){
        frame = (frame+1) % Animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

void Animation::clear(){
    SDL_DestroyTexture(texture);
};
#endif


// Bar class
Bar::Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone ){
    // Base bar
    Back_rect = dest;
    Front_rect = dest;
    color = newColor;
    // Icone part
    IconeTexture = Textures[icone];  // Texture of icone

    IconeRect = dest;
    SDL_QueryTexture(IconeTexture, NULL, NULL, &IconeRect.w, &IconeRect.h);
    //IconeRect.w = 14;
    //IconeRect.h = 16;

    IconeRect.y -= 2;
    IconeRect.x -= IconeRect.w + 2;
};

void Bar::blit( int width ){
    Front_rect.w = width;  // Setting width (health bar) 
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  // Drawing back part
    SDL_RenderFillRect(app.renderer, &Back_rect);  
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);  // Drawing front part
    SDL_RenderFillRect(app.renderer, &Front_rect);
    SDL_RenderCopy(app.renderer, IconeTexture, NULL, &IconeRect);  // Rendering icone
};



typeBox::typeBox(Uint8 size, float posX, float posY, const char* startText, ALIGNMENT_types newAligment, SDL_Color newColor){
    Font = createFont(size);
    dest.x = SCREEN_WIDTH * posX;
    dest.y = SCREEN_HEIGHT * posY - size/2;
    dest.w = dest.h = 0;

    aligment = newAligment;
    color = newColor;

    strcpy(buffer, startText);
    length = caret = strlen(buffer);
    if(caret){
        updateTexture();
    }

    // Creating background picture for typing
    SDL_QueryTexture(Textures[IMG_MENU_TYPE_BOX], NULL, NULL, &backRect.w, &backRect.h);
    backRect.x = SCREEN_WIDTH * posX - backRect.w/2;
    backRect.y = SCREEN_HEIGHT * posY - backRect.h/2 - 2;
}

typeBox::~typeBox(){
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}

// Creating new texture
void typeBox::updateTexture(){
    SDL_Surface* Surface = TTF_RenderUTF8_Solid(Font, buffer, color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_FreeSurface(Surface);
    dest.x += dest.w * aligment / 2;
    SDL_QueryTexture(Texture, NULL, NULL, &dest.w, &dest.h);
    dest.x -= dest.w * aligment / 2;
}

void swapChar(char* a, char* b){
    char t = *a;
    *a = *b;
    *b = t;
}

void typeBox::writeString(char* str, bool freeData){
    // Inserting text from clipboard
    Uint8 clipboardSize = strlen(str);

    // Checking, if all clipboard can be placed in buffer
    if(clipboardSize > bufferSize - length){
        clipboardSize = bufferSize - length;
    }

    // Moving part after caret at end
    for(Sint8 i = length; i >= caret; --i){
        buffer[i + clipboardSize] = buffer[i];
    }

    // Coping main clipboard text
    for(Uint8 i=0; i < clipboardSize; ++i){
        buffer[caret + i] = str[i];
    }

    length += clipboardSize;
    caret += clipboardSize;

    updateTexture();

    if(freeData){
        SDL_free(str);
    }
};

void typeBox::press(SDL_Keycode code){
    static SDL_Keycode preCode;
    switch (code)
    {
    case SDLK_BACKSPACE:
        // Coping after caret
        if(caret > 0){
            for(Uint8 t = --caret; t <= length; t++){
                buffer[t] = buffer[t+1];
            }
            length--;
        }
        break;

    case SDLK_DELETE:
        // Coping after caret
        if(caret < length){
            for(Uint8 t = caret + 1; t <= length; t++){
                buffer[t] = buffer[t+1];
            }
            length--;
        }
        break;
    
    case SDLK_LEFT:
        if(caret > 0){
            swapChar(buffer + caret--, buffer + caret - 1);
        }
        break;
    
    case SDLK_RIGHT:
        if(caret+1 < length){
            swapChar(buffer + caret++, buffer + caret + 1);
        }
        break;
    
    // Control-v mode
    case SDLK_PASTE:
        // Inserting text from clipboard
        writeString(SDL_GetClipboardText(), true);
        break;
        
    case SDLK_v:
        if(preCode == SDLK_LCTRL){
            writeString(SDL_GetClipboardText(), true);
        }
        break;

    case SDLK_LCTRL:
        if(preCode == SDLK_v){
            writeString(SDL_GetClipboardText(), true);
        }
        break;
    };
    updateTexture();
    preCode = code;
};

void typeBox::select(){
    buffer[length] = '|';
    caret = length++;
    buffer[length] = '\0';
    updateTexture();

    // Starting using keyboard
    SDL_StartTextInput();
};

void typeBox::removeSelect(){
    // Stoping entering any letters
    SDL_StopTextInput();

    for(Uint8 t = caret; t <= length; t++){
        buffer[t] = buffer[t+1];
    }
    length--;
    updateTexture();
};

void typeBox::updateCaret(){
    static char b[] = {' '};
    swapChar(buffer + caret, b);
    updateTexture();
};

bool typeBox::in(int x, int y){
    return ((x > backRect.x && x < backRect.x + backRect.w) &&
        (y > backRect.y && y < backRect.y + backRect.h));
};

void typeBox::blit(){
    // Rendering background picture for better typing
    SDL_RenderCopy(app.renderer, Textures[IMG_MENU_TYPE_BOX], NULL, &backRect);

    // Rendering text
    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);
};


// Dropbox class
DropBox::DropBox(SDL_Rect place, Uint8 newCount, char* newText, Uint8 size, SDL_Color newFrontColor, SDL_Color newBackColor){
    closeDest = place;
    count = newCount;
    Font = createFont(size);
    frontColor = newFrontColor;
    backColor = newBackColor;
    openDest = closeDest;
    state = 0;
    openDest.h *= count;
    text = newText;
}

DropBox::~DropBox(){
    for(int i=0; i < count; ++i){
        SDL_DestroyTexture(Texture[i]);
    }
    free(Texture);
}

void DropBox::updateText(LNG_types language){
    Texture = (SDL_Texture**)malloc(count * sizeof(SDL_Texture*));
    char txt[20];
    Uint8 textCounter = 0;
    
    for(Uint8 i=0; i < count; ++i){
        Uint8 bufferCounter = 0;
        for(; text[textCounter] != '\n'; ++textCounter){
            txt[bufferCounter++] = text[textCounter];
        }
        txt[bufferCounter] = '\0';
        SDL_Surface* Surface = TTF_RenderUTF8_Solid(Font, text + textCounter, frontColor);
        Texture[i] = SDL_CreateTextureFromSurface(app.renderer, Surface);
        SDL_FreeSurface(Surface);
    }
}

void DropBox::click(const int mouseX, const int mouseY){
    if(open){
        if((mouseX > openDest.x && mouseX < openDest.x + openDest.w) &&
        (mouseY > openDest.y && mouseY < openDest.y + openDest.h)){
            open = false;
            state = (mouseY - openDest.y) / openDest.h;
        }
    }
    else if((mouseX > closeDest.x && mouseX < closeDest.x + closeDest.w) &&
        (mouseY > closeDest.y && mouseY < closeDest.y + closeDest.h)){
            open = true;
        }
}

void DropBox::blit(){
    if(open){
        SDL_SetRenderDrawColor(app.renderer, backColor.r, backColor.g, backColor.b, backColor.a);
        SDL_RenderDrawRect(app.renderer, &closeDest);
    }
    else{
        SDL_SetRenderDrawColor(app.renderer, backColor.r, backColor.g, backColor.b, backColor.a);
        SDL_RenderDrawRect(app.renderer, &closeDest);
    }
}
