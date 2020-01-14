#ifndef MENUFIN_HPP_
#define MENUFIN_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

class MenuFin{
public:
	MenuFin();
	~MenuFin();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen,int death);
	int handleEvents();
	void update();
	void render();
	void clean();
	void setKill();
	void setBestScore();
	bool running(){return isrunning;}
private:
	bool isrunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	int killed;
};




#endif
