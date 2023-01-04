#include <stdio.h>
#include <SDL2/SDL.h>
#include "rectshape.h"

#define WIDTH 400
#define HIGHT 300
#define FRAMERATE 60


SDL_Renderer *renderer;
SDL_Window *window;
rectShape *first;
rectShape *last;


void draw(){
        SDL_SetRenderDrawColor(renderer,255,255,255,255);//the whole window
        SDL_RenderClear(renderer);

    rectShape*item=first;
    while(item!= NULL){
        rectshape_draw(item,renderer);
        item=item->next;

    }


        SDL_RenderPresent(renderer);//display

}

void addrectshape(struct rectShape*rectshape){
        if(last!=NULL){
            last->next=rectshape;
            rectshape->pre=last;
            last=rectshape;
        }else{
            last=rectshape;
            first=rectshape;
        }
    }

    void event_loop(){
        rectShape*item;
        while(1){
            uint32_t begin=SDL_GetTicks();
            //creat the circle(xunhuan),drawing
            draw();

            SDL_Event event;//define the name
            while(SDL_PollEvent(&event)){
                switch (event.type) {
                                case SDL_MOUSEMOTION:
                                case SDL_MOUSEBUTTONDOWN:
                                case SDL_MOUSEBUTTONUP:
                                    item=last;
                                    while(item!= NULL){

                                        if(rectshape_onmouse_event(item, &event)) {
                                            if (item != last) {
                                                if (item->pre != NULL) {
                                                    item->pre->next = item->next;
                                                } else {
                                                    first = item->next;
                                                }
                                                item->next->pre = item->pre;
                                                item->next = NULL;
                                                addrectshape(item);
                                            }

                                        }
                                        item=item->pre;
                                    }
                                break;

                                 case SDL_QUIT:
                                     return;

                }

                }

             long current=SDL_GetTicks();
             long cost=current-begin;
             long frame=1000/FRAMERATE;
             long delay=frame-cost;

            if(delay>0) {
                SDL_Delay(20);//50HZ
            }
        }
}
    int main(void){
        //creat the whole window
    if(SDL_Init(SDL_INIT_VIDEO)){
        //using the linux's video to creat the window
        SDL_Log("Can not init video,%s",SDL_GetError());
        return 1;
    }

    window= SDL_CreateWindow("Game",
                                      SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                      WIDTH,HIGHT,
                                      SDL_WINDOW_SHOWN);//define win

    if(window==NULL){
        SDL_Log("Can not creat window,%s",SDL_GetError());
        return 2;
    }
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer==NULL){
        SDL_Log("Can not creat render,%s",SDL_GetError());

}
        first=NULL;
        last=NULL;

        addrectshape(rectshape_creat(0,0,80,60,0xffff0000));
        addrectshape(rectshape_creat(100,0,80,60,0xffffff00));
        addrectshape(rectshape_creat(200,0,80,60,0xff0000ff));

        event_loop();
        rectShape*item=first;
        while(item!= NULL){
            rectShape *current=item;
            item=item->next;
            destory_rectshape(current);
        }
        first=NULL;
        last=NULL;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

    return 0;
}
