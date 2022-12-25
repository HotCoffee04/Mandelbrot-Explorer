#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "frac.h"


//indexes of the textures to be used on the "textures" array
typedef enum TextureIndex{

	T_Loads,

}TextureIndex;

SDL_Rect *texPos;

//textures, I'm only going to need one.
SDL_Texture *textures[512];

void r_init(SDL_Renderer *rend);
void g_getInput();
int g_logic();
void r_renderToTexture(SDL_Texture *renderTexture);
