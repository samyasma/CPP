#ifndef MENU_HPP_
#define MENU_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

class Menu{
public:
	Menu();
	~Menu();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	int handleEvents();
	void update();
	void render();
	void clean();
	bool running(){return isrunning;}
private:
	bool isrunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
};




#endif