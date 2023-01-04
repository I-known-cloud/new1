//
// Created by dongran on 23-1-3.
//
#include <SDL2/SDL.h>
#ifndef DRAGRECT_RECTSHAPE_H
#define DRAGRECT_RECTSHAPE_H

typedef struct rectShape {
    SDL_FRect dest;
    uint32_t color;
    SDL_FPoint dragstart;
    SDL_FPoint dragmousestart;
    int drag_can;
    struct rectShape *pre;
    struct rectShape *next;

}rectShape;

rectShape *rectshape_creat(float x, float y, float  w, float h, uint32_t color);

void rectshape_draw(rectShape*self, SDL_Renderer*renderer);

SDL_bool rectshape_onmouse_event(rectShape*self, SDL_Event*event);

void destory_rectshape(rectShape*self);

#endif //DRAGRECT_RECTSHAPE_H
