#include "game.h"
#include "resource.h"

//renderer
SDL_Renderer *rend;

int close;
int update = 1;
int loadingUpdate = 0;
int dragging = 0;

Point curs;

//function that draws fractal on render texture
void r_drawFractal();
//scaling of coordinates
void scaleCoords(int* x,int* y);

SDL_Color zeroCol = {0,76,20}; //color used for points outside the set
SDL_Color middleCol = {255,255,255}; //color given to points that result in 0.5
SDL_Color oneCol = {0,0,0}; //color used for points inside the set

//get color from value of plotted point
SDL_Color colorFromValue(double v);

SDL_Texture *r_loadTexture(char *name); //loads a single texture
void r_loadTextures(); //loads every texture

void r_cleanup();



void r_init(SDL_Renderer *r){
	close = 1;
	rend = r;

	SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);

	r_loadTextures();
}


void r_renderToTexture(SDL_Texture *renderTexture){

	SDL_SetRenderDrawColor(rend,8,8,8,255);
	SDL_SetRenderTarget(rend,renderTexture);

	if(update && !loadingUpdate)
	SDL_RenderClear(rend);


	SDL_Rect pos;
	pos = (SDL_Rect){0,0,SCREENWIDTH,SCREENHEIGHT};

	if(update){

		if(loadingUpdate){
			SDL_RenderCopy(rend,textures[T_Loads],0,&(SDL_Rect){0,SCREENHEIGHT-80,265,80});
			SDL_RenderPresent(rend);
			loadingUpdate = 0;
			goto end;
		}

		r_drawFractal();

		update = 0;

	}

	end:
	SDL_SetRenderTarget(rend,0);
}

void r_drawFractal(){

	double c;
	SDL_Color col;
	for(int x = 0; x < SCREENWIDTH; x++){

		for(int y = 0; y < SCREENHEIGHT; y++){

			col = colorFromValue(getFracPoint(x,y));
			SDL_SetRenderDrawColor(rend,col.r,col.g,col.b,255);
			SDL_RenderDrawPoint(rend,x,y);
		}

	}


}

void g_getInput(){

	int x,y;
	SDL_GetMouseState(&x,&y);
	scaleCoords(&x,&y);


	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				close = 0;
			break;
			case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_RESIZED)
					close = 2;
			break;
			case SDL_MOUSEMOTION:

			break;
			case SDL_MOUSEBUTTONDOWN:

				if(event.button.button == SDL_BUTTON_LEFT){
					dragging = 1;
					curs = (Point){x,y};
				}else{
					update = 1;
					loadingUpdate = 1;
				}

			break;
			case SDL_MOUSEBUTTONUP:


				if(event.button.button == SDL_BUTTON_LEFT){
					if(dragging){
						//move plotting
						Point nSt,nEnd;
						Point pSt = getPlotStart();
						Point pEnd = getPlotEnd();
						double dist = pdistance(curs,(Point){x,y});
						nSt.x = pSt.x + ((curs.x - x)/SCREENWIDTH) * (pEnd.x - pSt.x);
						nSt.y = pSt.y + ((curs.y - y)/SCREENHEIGHT) * (pEnd.y - pSt.y);
						setPlotStart(nSt.x,nSt.y);
						nEnd.x = pEnd.x + (nSt.x - pSt.x);
						nEnd.y = pEnd.y + (nSt.y - pSt.y);
						setPlotEnd(nEnd.x,nEnd.y);
						update = 1;
						loadingUpdate = 1;

					}
					dragging = 0;

					}

			break;

				

			case SDL_KEYDOWN:

				if(event.key.keysym.scancode == SDL_SCANCODE_UP || event.key.keysym.scancode == SDL_SCANCODE_DOWN){



					Point pSt = getPlotStart();
					Point pEnd = getPlotEnd();

					Point mid,nmid;
					mid.x = pSt.x+(pEnd.x - pSt.x)/2;
					mid.y = pSt.y+(pEnd.y - pSt.y)/2;

					if(event.key.keysym.scancode == SDL_SCANCODE_UP){
						nmid.x = mid.x*2;
						nmid.y = mid.y*2;
						setZoom(getZoom()*2);
					}
					else{
						nmid.x = mid.x/2;
						nmid.y = mid.y/2;
						setZoom(getZoom()/2);
					}

					setPlotStart(getPlotStart().x - (mid.x - nmid.x),getPlotStart().y - (mid.y - nmid.y));
					setPlotEnd(getPlotEnd().x - (mid.x - nmid.x),getPlotEnd().y - (mid.y - nmid.y));


					update = 1;
					loadingUpdate = 1;
				}
			break;
			default:
				close = 1;
			break;
		}
	}
	
}

int g_logic(){

	if(!close)
		r_cleanup();

	return close;

}

void r_cleanup(){

}

void scaleCoords(int* x,int* y){


	//scales coordinates
	int nx,ny;
	nx = texPos->w+texPos->x*2;
	ny = texPos->h+texPos->y*2;
	float winScale;
	float ratio = (float)nx / ny;

	if(ratio > (SCREENWIDTH/(float)SCREENHEIGHT))
	winScale = (float)ny/SCREENHEIGHT;
	else
	winScale = (float)nx / (float)SCREENWIDTH;

	*x -= texPos->x;
	*y -= texPos->y;
	*x = *x / winScale;
	*y = *y / winScale;


}

SDL_Texture *r_loadTexture(char *name){

	//actually loads it from constant memory
	SDL_Surface *surf;
	SDL_Texture *tex;
	SDL_RWops *ops;


	ops = SDL_RWFromConstMem(loads,84938);
	
	surf = SDL_LoadBMP_RW(ops,0);
	tex = SDL_CreateTextureFromSurface(rend,surf);

	SDL_FreeSurface(surf);
	free(ops);
	return tex;
}

void r_loadTextures(){

	textures[T_Loads] = r_loadTexture("loads.bmp");
}

SDL_Color colorFromValue(double v){

	if(!COL){

		return (SDL_Color){ ceil(255-(v*255)),ceil(255-(v*255)),ceil(255-(v*255)),255 };

	}else{

		return (SDL_Color){ (v*255),(v*255),(v*255),255 };

		if(v < 0.5)
		return (SDL_Color){ zeroCol.r+(middleCol.r-zeroCol.r)*v,zeroCol.g+(middleCol.g-zeroCol.g)*v,zeroCol.b+(middleCol.b-zeroCol.b)*v,255 };

		if(v == 0.5)
		return (SDL_Color){255,255,255,255};

		if(v > 0.5)
		return (SDL_Color){ middleCol.r+(oneCol.r-middleCol.r)*v,middleCol.g+(oneCol.g-middleCol.g)*v,middleCol.b+(oneCol.b-middleCol.b)*v,255 };
	}


}