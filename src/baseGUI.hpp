#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Namespace of objects for UI
namespace GUI{

    // Text alignment type
    enum ALIGNMENT_types{
        LEFT_text,
        MIDLE_text,
        RIGHT_text
    };

    // Static text on screen with drawing functions
    class staticText
    {
    private:
        const static Uint8 BUFFER_SIZE = 50;  // Length of buffers for text
        char *text;                // Text to show on screen
        Uint8 fontHeight;          // Font size to create font
        float posX, posY;          // Relative positions on screen
        ALIGNMENT_types aligment;  // Aligment type to improve displasment
        SDL_Color color;           // Base draw color

        TTF_Font* Font;            // Font to create texture
        SDL_Texture *Texture;      // Texture of text
        SDL_Rect Rect;             // Position to draw
    public:
        staticText(char* newText, Uint8 newSize, float newX, float newY, SDL_Color newColor = WHITE, ALIGNMENT_types newAlignment = MIDLE_text);
        void init();                      // Creating font seted size
        void free();                      // Free texture and font
        void updateText(int number = 0);  // Create new texture with displasment '%' to entered number
        void blit();                      // Drawing selected text
    };

    // Class of slider bar with point on it to control some parameter
    class Slider{
    private:
        SDL_Texture *textureLine;
        SDL_Texture *textureButton;
        SDL_Rect destLine;
        SDL_Rect destButton;
    public:
        Slider(const float Y, const IMG_names lineImage = IMG_MENU_SCROLLER_LINE, const IMG_names buttonImage = IMG_MENU_SCROLLER_BUTTON);  // Create slide with need line and button images
        void blit(Uint8 state);  // Drawing slider with need button position
        bool in(int X, int Y);   // Check, if mouse press on current area
        int getX();              // Getting current position of button
    };

    // Class of GUI objects, which use to activate something
    class Button
    {
    private:
        float posX, posY;        // Relative positions on screen
        IMG_names textureIndex;  // Index of texture from IMG_names
        SDL_Rect dest;           // Position of current button
        staticText* topText;     // Pointer to text on this button (shortcut)
    public:
        Button(float X, float Y, IMG_names textureIndex, staticText* top = nullptr);  // Create new button, posible with pointer to text on it
        void init();                      // Initialise position, width and height of current button
        void blit();                      // Drawing current button
        bool in(int mouseX, int mouseY);  // Check, if mouse press on current area
    };

    // Class of objects, which show GIF-animations
    #if ANI_count
    class Animation
    {
    private:
        ANI_names type;
        SDL_Texture* texture;
        Uint32 frame;
        Uint64 prevTick;
        SDL_Rect dest;
    public:
        Animation( SDL_Rect destination, ANI_names newType );
        void blit();
        void clear();
    };
    #endif


    // Bar to show some charachteristic (like health) with icone
    class Bar
    {
    private:
        SDL_Rect Back_rect;         // Background rect for second color
        SDL_Rect Front_rect;        // Front rect for primal color
        SDL_Rect IconeRect;         // Rect for icone, near bar
        SDL_Texture* IconeTexture;  // Icone texture, or NULL, if not need
        SDL_Color color;
    public:
        Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone);  // Create new bar with it position, primal color and icone near it
        void blit( int width );  // Drawing bar with icone need width
    };

    // Class of box, where user can type text
    class typeBox
    {
    private:
        // Global class constants
        const static Uint8 bufferSize = 16;

        // Constants from creating
        ALIGNMENT_types aligment;  // Aligment type for correct placed position
        SDL_Color color;           // Color of typing text

        // Variables
        Uint8 caret;               // Position of place, where user type
        Uint8 length;              // Length of all text
        TTF_Font* Font;            // Font for type text
        SDL_Rect dest;             // Rectangle, where text draw
        SDL_Texture* Texture;      // Generated texture of text
        SDL_Rect backRect;         // Rectangle of background plate (for better visability)

        void updateTexture();      // System function of creating new texture and updating his position

    public:
        char buffer[bufferSize + 1];  // Read only data, which write in this typebox

        typeBox(Uint8 size, float posX, float posY, const char* startText = "", ALIGNMENT_types newAligment = MIDLE_text, SDL_Color newColor = BLACK);
        ~typeBox();                                  // Clearing font and texture
        void blit();                                 // Function of drawing text with background plate
        void writeString(char* str, bool freeData);  // Function of writing any string to buffer at caret position
        void press(SDL_Keycode code);                // Function of processing special keycodes
        void updateCaret();                          // Function of change caret symbol from '|' to ' ' and back
        void select();                               // Function of setting caret for typing after
        void removeSelect();                         // Function of removing caret after typing
        bool in(int mouseX, int mouseY);             // Function of checking, if mouse press on this typeBox
    };

    
    // Class of object to select from some variants
    // !WIP
    class DropBox
    {
    private:
        SDL_Rect closeDest;
        SDL_Rect openDest;
        TTF_Font* Font;
        SDL_Texture **Texture;
        SDL_Color backColor;
        SDL_Color frontColor;
        Uint8 count;
        Uint8 state;
        bool open;
        char* text;
    public:
        DropBox(SDL_Rect place, Uint8 newCount, char* newText, Uint8 size, SDL_Color newFrontColor = BLACK, SDL_Color newBackColor = WHITE);
        ~DropBox();
        void updateText();
        void click(const int mouseX, const int mouseY);
        void blit();
    };
}