#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>

#define r1Startx 350
#define r1Starty 200
#define r2Startx 150
#define r2Starty 200
SDL_Rect r1 = { r1Startx,r1Starty, 50, 50 };
SDL_Rect r2 = { r2Startx,r2Starty,35,35};
SDL_MouseButtonEvent* mouse;
int r1max = 50 ,r2max = 50;
int r1s = 0,r2s = 0 ;
int r1sl = 0,r2sl = 0;

SDL_Event e;
SDL_Renderer* renderer;

Uint32 now,delay,last;

void move(SDL_Rect* rec,int * s,int max,int startx, int starty, int inc){
	if(!(*s==0 || *s==1))inc *= -1;

	if(*s==0){
		if(rec->x+inc > startx+max) *s=1;
		else rec->x+=inc;
	}else if(*s==1){
		if(rec->y+inc > starty+max) *s=2;
		else rec->y+=inc;
	}else if(*s==2){
		if(rec->x+inc < startx) *s=3;
		else rec->x+=inc;
	}else if(*s==3){
		if(rec->y+inc < starty) *s=0;
		else rec->y+=inc;
	}
}
int testClick(SDL_MouseButtonEvent* me, SDL_Rect* rec)
{
	if ((me->y >= rec->y) && (me->y <= rec->y + rec->h) &&
	    (me->x >= rec->x) && (me->x <= rec->x + rec->w))
		return 1;
	else return 0;
}


void loop(){
	SDL_PollEvent(&e);
	now = SDL_GetTicks();
	if (e.type == SDL_MOUSEBUTTONDOWN)
        {
		mouse = (SDL_MouseButtonEvent*) &e;
		if ((e.button.button == SDL_BUTTON_LEFT) && testClick(mouse, &r1)==1)
			r1sl = 1;	

		if ((SDL_BUTTON_LEFT) && testClick(mouse, &r2)==1)
			r2sl = 1;	
                    
        }
	
	if(now > last + delay){
		last = SDL_GetTicks();
		if (r1sl == 0)
			move(&r1,&r1s,r1max,r1Startx,r1Starty, 7);
		if (r2sl == 0)
			move(&r2,&r2s,r2max,r2Startx,r2Starty, 5);
	}


	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(renderer, NULL);

        SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(renderer, &r1);
        SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(renderer, &r2);

        SDL_RenderPresent(renderer);
}
int main (int argc, char* args[])
{
    /* INITIALIZATION */

    int err = SDL_Init(SDL_INIT_EVERYTHING);
    assert(err == 0);

    SDL_Window* window = SDL_CreateWindow("Input",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            640, 480, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,0);

    /* EXECUTION */

	delay = 33;
    
    while (1){
		if (e.type == SDL_QUIT) {
		    break;
		} 
		loop();
	}

    /* FINALIZATION */

    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
