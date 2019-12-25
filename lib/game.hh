#ifndef GAME_HPP_
#define GAME_HPP_

#include "SDL2/SDL.h"
#include <iostream>
#include <stdio.h>

class Game{
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handleEvents();
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