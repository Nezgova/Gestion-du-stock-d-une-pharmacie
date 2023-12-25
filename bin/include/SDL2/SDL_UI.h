#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define BUILD_DLL
#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    int border_radius;
    bool (*onClick)(void* data);
    void* onClickData;
} UIElement_t;

typedef struct {
    UIElement_t base;
    TTF_Font* font;
    const char* label;
    SDL_Color normalColor;
    SDL_Color hoverColor;
    bool isHovered;
} UIButton_t;

typedef struct {
    UIElement_t base;
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Color bgColor;
    char text[100];
    int maxValue;
    bool isEditable;
} UITextField_t;

typedef struct {
    UIElement_t base;
    int minValue;
    int maxValue;
    int* linkedValue;
    bool isDragging;
} UIScrollbar_t;


typedef struct {
    UIElement_t base;
} UIPlacementField_t;

EXPORT SDL_Texture* loadImage(SDL_Renderer* renderer, const char* filename);
EXPORT bool pointInRect(int x, int y, SDL_Rect rect);
EXPORT bool pointInRoundRect(int x, int y, UIElement_t* element);
EXPORT bool buttonOnClick(void* data);
EXPORT bool textfieldOnClick(void* data);
EXPORT bool scrollbarOnClick(void* data);
EXPORT void scrollbarOnScroll(void* data, int deltaY);

EXPORT void handleResize(UIElement_t* elements, int numElements, int windowWidth, int windowHeight);
EXPORT void handleEditableTextFieldEvents(UITextField_t* textField, SDL_Event* event, char* str);
EXPORT void updateButtonState(UIButton_t* button, int mouseX, int mouseY);

EXPORT void renderUIElement(SDL_Renderer* renderer, UIElement_t* element);
EXPORT void renderRoundRect(SDL_Renderer* renderer, UIElement_t* element);
EXPORT void renderButtonRr(SDL_Renderer* renderer, UIButton_t* button, bool isRound, SDL_Color fontcolor);
EXPORT void renderTextFieldRr(SDL_Renderer* renderer, UITextField_t* textField, bool isRound, SDL_Color fontcolor, char* text);
EXPORT void renderScrollbarRr(SDL_Renderer* renderer, UIScrollbar_t* scrollbar, bool isRound);
EXPORT void renderPlacementFieldRr(SDL_Renderer* renderer, UIPlacementField_t* placementField, bool isRound);
EXPORT void renderImage(SDL_Renderer* renderer, UIElement_t* image);
EXPORT void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, SDL_Rect position);