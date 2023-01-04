//
// Created by dongran on 23-1-3.
//

#include "rectshape.h"



rectShape *rectshape_creat(float x, float y, float  w, float h, uint32_t color){
    rectShape *self= malloc(sizeof(rectShape));
    self->color=color;
    self->dest.x=x;
    self->dest.y=y;
    self->dest.w=w;
    self->dest.h=h;
    self->pre=NULL;
    self->next=NULL;
    self->drag_can=0;
    return self;
}

void rectshape_draw(rectShape*self, SDL_Renderer*renderer){
    SDL_SetRenderDrawColor(renderer,
                           (self->color&0x00ff0000)>>16,
                           (self->color&0x0000ff00)>>8,
                           self->color&0x000000ff,
                           (self->color&0xff000000)>>24
    );
    SDL_RenderFillRectF(renderer,&(self->dest));
}

SDL_bool rectshape_onmouse_event(rectShape*self, SDL_Event*event){
    SDL_Point current_mouse_point={event->button.x,event->button.y};
    SDL_Rect destrect={(int)self->dest.x,(int)self->dest.y,(int)self->dest.w,(int)self->dest.h};

    switch (event->type) {

        case SDL_MOUSEMOTION:
            if(self->drag_can){
                self->dest.x=self->dragstart.x+event->motion.x-self->dragmousestart.x;//bereturn SDL_FALSE;hind two is pian yi liang which can get the information of the set and rnew
                self->dest.y=self->dragstart.y+event->motion.y-self->dragmousestart.y;
                return SDL_TRUE;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:

            if(SDL_PointInRect(&current_mouse_point,&destrect)) {

                self->dragstart.x = self->dest.x;
                self->dragstart.y = self->dest.y;
                self->dragmousestart.x = event->button.x;
                self->dragmousestart.y = event->button.y;
                self->drag_can = 1;
                return SDL_TRUE;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(SDL_PointInRect(&current_mouse_point,&destrect)) {
                self->drag_can = 0;
                return SDL_TRUE;
            }
            break;


    }
    return SDL_FALSE;

}

void destory_rectshape(rectShape*self){
    free(self);
}
