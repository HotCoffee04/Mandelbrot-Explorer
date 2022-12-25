#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <Windows.h>

#include "common.h"
#include "game.h"

/*
	Scales the render texture based on the size of the window.
*/
void resizedWindow();

SDL_Window *win;
SDL_Rect texturePos;

float winScale; //scale of window

int APIENTRY WinMain(HINSTANCE h, HINSTANCE h2, LPSTR l, int i){

	//get command line parameters
	char delimiter[2] = " ";
	char prev[15];
	char *word;
	word = strtok(l, delimiter);

	int iter,res,col;
	col = 0;
	iter = 256;
	res = 1024;

	while( word != NULL ) {

		strcpy(prev,word);

		if(!strcmp(word,"-col"))
			col = 1;

		word = strtok(NULL, delimiter);

		if(word != NULL){
			if(!strcmp(prev,"-iter"))
				iter = atoi(word);
			
			if(!strcmp(prev,"-res"))
				res = atoi(word);

		}
	}

	if(iter < 2)
		iter = 128;
	if(res < 16)
		res = 128;

	SCREENHEIGHT = SCREENWIDTH = res;

	ITERS = iter;

	COL = col;

	//init SDL
	SDL_Init(SDL_INIT_VIDEO);

	win  = SDL_CreateWindow("Mandelbrot Explorer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREENWIDTH,SCREENHEIGHT,SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	//SDL_MaximizeWindow(win);

	//cycle through all the renderers and find OpenGL
	SDL_Renderer* rend = 0;
	for( int i = 0; i < SDL_GetNumRenderDrivers(); ++i )
	{
		SDL_RendererInfo rendererInfo;
		SDL_GetRenderDriverInfo( i, &rendererInfo );
		if(strcmp(rendererInfo.name,"opengl") != 0)
		{
			continue;
		}

		rend = SDL_CreateRenderer( win, i, 0 );
		break;
	}

	/* I use an SDL texture and draw everything on it and then properly scale it to fit the window */
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
	SDL_Texture *renderTexture; 
	renderTexture = SDL_CreateTexture(rend,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREENWIDTH,SCREENHEIGHT);

	texturePos.h = SCREENHEIGHT;
	texturePos.w = SCREENWIDTH;
	texturePos.x = 0;
	texturePos.y = 0;

	texPos = &texturePos;

	resizedWindow();

	r_init(rend);

	int close = 0;
	while (!close) //main loop
	{
		SDL_SetRenderDrawColor(rend,0,0,0,255);
		SDL_RenderClear(rend);

		g_getInput(); //gets user input

		switch(g_logic()){ //based on input decides what to do
			case 0:
				close = 1;
				break;
			case 2:
				resizedWindow();
			break;
		}

		r_renderToTexture(renderTexture); //updates render texture

		SDL_RenderCopy(rend,renderTexture,0,&texturePos); //draws render texture on the window

		SDL_RenderPresent(rend); //shows render

		//60 fps
		SDL_Delay(1000/60); //used to keep the program at 60 frames per second.

	}

	//cleans up
	SDL_DestroyTexture(renderTexture);
	SDL_DestroyWindow(win);
	SDL_Quit();
}


void resizedWindow(){

	int nx,ny;
	SDL_GetWindowSize(win,&nx,&ny);
	int sx,sy;

	float ratio = (float)nx / ny;

	texturePos.x = texturePos.y = 0;

	if(ratio > (SCREENWIDTH/(float)SCREENHEIGHT)){
		//X is bigger than Y
		winScale = (float)ny/SCREENHEIGHT;

		sx = (SCREENHEIGHT*(SCREENWIDTH/(float)SCREENHEIGHT)) * winScale;
		sy = SCREENHEIGHT * winScale;

		texturePos.x = (float)nx / 2 - ( (float)sx/2);
	}else{
		//Y is bigger than X
		winScale = (float)nx / (float)SCREENWIDTH;

		sx = SCREENWIDTH * winScale;
		sy = (SCREENWIDTH / (SCREENWIDTH/(float)SCREENHEIGHT)) * winScale;

		texturePos.y = (float)ny / 2 - ( (float)sy/2);
	}

	texturePos.h = sy;
	texturePos.w = sx;
}