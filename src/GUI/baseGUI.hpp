/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <array>
#include "../data/app.hpp"


// Namespace of objects for GUI (Graphic User Interface)
namespace GUI {
    // Text aligment type
    enum class Aligment : unsigned {
        Left,
        Midle,
        Right,
    };


    // Object, that will be drawn at screen
    class Template {
     protected:
        const Window& window;

     public:
        Template(const Window& window);
        virtual void blit() const;
    };


    // Object with texture, that will be drawn
    class TextureTemplate : public Template {
     protected:
        SDL_Texture* texture;
        SDL_FRect rect;

     public:
        TextureTemplate(const Window& window);
        void move(float X, float Y);
        void blit() const override;
        virtual bool in(const Mouse mouse) const;
    };


    // Class of rounded backplate for better understability
    class RoundedBackplate : public TextureTemplate {
     public:
        RoundedBackplate(const Window& window, float centerX, float centerY, float width, float height,
            float radius, float border, Color frontColor = GREY, Color backColor = BLACK);
        RoundedBackplate(const Window& window, const SDL_FRect& rect, float radius, float border,
            Color frontColor = GREY, Color backColor = BLACK);
        ~RoundedBackplate();
    };


    // Class with rectangular backplate for typeBox
    class RectBackplate : public TextureTemplate {
     public:
        RectBackplate(const Window& window, float centerX, float centerY, float width, float height,
            float border, Color frontColor = GREY, Color backColor = BLACK);
        RectBackplate(const Window& window, const SDL_FRect& rect,
            float border, Color frontColor = GREY, Color backColor = BLACK);
        ~RectBackplate();
    };


    // Textures
    #if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
    // Class of slider bar with point on it to control need parameter
    class Slider : public TextureTemplate {
     private:
        SDL_Texture *textureButton;  // Texture of line (upper part of slider)
        SDL_FRect buttonRect;        // Place for rendering upper part
        const unsigned maxValue;     // Maximal value of state

     public:
        // Create slide with need line and button images
        Slider(const Window& window, float X, float Y, float width, unsigned startValue,
            Textures lineImage = Textures::SliderLine, Textures buttonImage = Textures::SliderButton, unsigned max = 255);
        unsigned setValue(float mouseX);  // Setting new state from mouse position
        unsigned scroll(float wheelY);    // Checking mouse wheel action
        void blit() const override;       // Drawing slider with need button position
    };


    // Class of buttons with image on it
    class ImageButton : public TextureTemplate {
     public:
        ImageButton(const Window& window, float X, float Y, float width, Textures name);
    };
    #endif


    // Animations
    #if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
    class Animation : public TextureTemplate {
     private:
        const Animations type;
        const IMG_Animation* animation;
        unsigned frame = 0;
        timer prevTick;

     public:
        Animation(const Window& window, float X, float Y, float width, float height, Animations type);
        Animation(const Window& window, const SDL_FRect& destination, Animations type);
        ~Animation();
        void update();
    };
    #endif


    // Text part
    #if (USE_SDL_FONT) && (PRELOAD_FONTS)
    // Static text on screen
    class StaticText : public TextureTemplate {
     public:
        StaticText(const Window& window, float X, float Y, const LanguagedText texts,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        ~StaticText();
    };


    // Static text on screen
    class HighlightedStaticText : public TextureTemplate {
     public:
        HighlightedStaticText(const Window& window, float X, float Y, const LanguagedText texts, int frameThickness,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        ~HighlightedStaticText();
    };


    // Dynamicly updated text on screen
    class DynamicText : public TextureTemplate {
     private:
        const LanguagedText texts;  // Text to create from
        const float posX;           // Relative positions on screen
        const Aligment aligment;    // Aligment type to improve displasment
        const Color color;          // Base draw color
        const float height;         // Height of text to draw

     public:
        DynamicText(const Window& window, float X, float Y, const LanguagedText texts,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        ~DynamicText();
        template <typename ...Args>
        void setValues(Args&& ...args) {
            // Checking for all chars
            char buffer[100];
            std::snprintf(buffer, sizeof(buffer), texts.getString().c_str(), args...);

            // Creating surface with text
            texture = window.createTexture(Fonts::Main, height, buffer, 0, color);

            // Moving draw rect to new place
            rect.w = texture->w;
            rect.h = texture->h;
            rect.x = window.getWidth() * posX - (rect.w * (unsigned)aligment / 2);
        }
    };


    // Class of field, where user can type text
    template <unsigned bufferSize = 16>
    class TypeField : public TextureTemplate {
     protected:
        // Class constants
        const int posX;                    // Relevant x position on screen
        const Aligment aligment;           // Aligment type for correct placed position
        const Color textColor;             // Color of typing text
        TTF_Font* font;                    // Font for type text

        // Variables
        char buffer[bufferSize+1];         // String, that was typed
        size_t length = 0;                 // Length of all text
        size_t caret = 0;                  // Position of place, where user type
        timer needSwapCaret = 0;           // Time, when next need to change caret
        int selectLength = 0;              // Length of selected box

        bool showCaret = false;            // Flag, if need to show caret
        SDL_FRect caretRect;               // Place, where caret should be at screen
        SDL_FRect inversedRectDest;        // Rect of inversed selected text, where should be drawn
        SDL_FRect inversedRectSrc;         // Part of text, that should be reversed (relative)
        SDL_Texture* inverseTexture;       // Texture of inversed selected box
        char clipboardText[bufferSize+1];  // Copying string for clipboard use
        bool pressed = false;              //
        bool selected = false;             //

        void updateTexture();              // Creat new texture of updated text
        void updateSelected();             // Update reversed rect position (selected part)
        void deleteSelected();             // Clearing selected part
        void writeClipboard();             // Write clipboard content after caret
        void copyToClipboard();            // Writing selected text to clipboard

     public:
        TypeField(const Window& window, float posX, float posY, const char *startText = "",
            float height = Height::TypeBox, Aligment aligment = Aligment::Midle, Color textColor = BLACK);
        ~TypeField();                        // Clearing font and texture
        void writeString(const char* str);   // Function of writing any string to buffer at caret position
        void type(SDL_Keycode code);         // Function of processing special keycodes
        void update(float mouseX);           // Function of change caret symbol from '|' to ' ' and back
        bool click(const Mouse mouse);       // Function of setting caret for typing after
        void unclick();                      // Function of resetting pressing
        const char* getString();             // Function of getting typed string
        void setString(const char* string);  // Function for replace text with new string
        void blit() const override;          // Function for draw at screen
    };


    // Object for typying in text with backplate for visability
    template <unsigned bufferSize = 16>
    class TypeBox : public TypeField<bufferSize> {
     private:
        RectBackplate backplate;

     public:
        TypeBox(const Window& window, float posX, float posY, const char *startText = "", float height = Height::TypeBox,
            Aligment aligment = Aligment::Midle, unsigned frameWidth = 2, Color textColor = BLACK);
        void blit() const override;  // Function for draw inputting text with backplate
        bool in(const Mouse mouse) const override;
    };


    // Class of buttons with text on it
    class TextButton : public HighlightedStaticText {
     private:
        const RoundedBackplate backplate;

     public:
        TextButton(const Window& window, float X, float Y, const LanguagedText texts, float size = Height::Main,
            Color color = WHITE, Aligment aligment = Aligment::Midle);
        void blit() const override;
    };


    // Class of appearing for time and hidden by time text
    class InfoBox : public HighlightedStaticText {
     private:
        unsigned counter = 0;
        static const unsigned maxCounter = 100;

     public:
        InfoBox(const Window& window, float X, float Y, const LanguagedText texts,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        void update();
        void reset();
    };


    // Class for box with message and actions with it
    class TwoOptionBox : public Template {
     private:
        // Flag of showing
        bool active = false;

        // Background plate for better visability
        const GUI::RoundedBackplate background;
        // Main text - title
        const GUI::HighlightedStaticText mainText;
        // Select variants
        const TextButton button1, button2;

     public:
        TwoOptionBox(const Window& window, const LanguagedText title,
            const LanguagedText button1Text, const LanguagedText button2Text);
        int click(const Mouse mouse);  // Return 1, if active; 2 if 1 button pressed; 3 if 2 button pressed
        void activate();
        void reset();
        bool isActive() const;
        void blit() const override;
    };


    // Class for box with message and actions with it
    class OneOptionBox : public Template {
     private:
        // Flag of showing
        bool active = false;

        // Background plate for better visability
        const GUI::RoundedBackplate background;
        // Main text - title
        const GUI::HighlightedStaticText mainText;
        // Select variants
        const TextButton button;

     public:
        OneOptionBox(const Window& window, const LanguagedText title,
            const LanguagedText buttonText);
        int click(const Mouse mouse);  // Return 1, if active; 2 if button pressed
        void activate();
        void reset();
        bool isActive() const;
        void blit() const override;
    };

    #endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)

}  // namespace GUI
