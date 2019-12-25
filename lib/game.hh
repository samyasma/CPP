#ifndef GAME_HPP_
#define GAME_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../lib/personnage.hh"
#include "../lib/terrain.hh"
#include "../lib/smoke.hh"
#include "../lib/samy.hh"


class Game{
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	void generateSmoke();
	bool running(){return isrunning;}
private:
	bool isrunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<Smoke*> v;
	Samy* samy;
};

#endif