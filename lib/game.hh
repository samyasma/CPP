#ifndef GAME_HPP_
#define GAME_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../lib/personnage.hh"
#include "../lib/terrain.hh"
#include "../lib/smoke.hh"
#include "../lib/samy.hh"
#include "../lib/bazooka.hh"
#include "../lib/dragonball.hh"
#include <chrono>


class Game{
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int difficulty, bool soviet_mode);
	void handleEvents();
	void update();
	void render();
	void clean();
	void generateSmoke();
	bool running(){return isrunning;}
	void setHealthStamina();
	void setText();
	int getKilled(){return killed;}
	void weaponupdate(Samy* samy);
	std::vector<Smoke*> getListSmoke(){return smokeVec;}
	void setScore();
	void setTimer();
private:
	unsigned int _difficulty;
	bool isrunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<Smoke*> smokeVec;
	std::vector<Bullet*> bulletVec;
	std::vector<Samy*> Players;
	std::vector<Weapon*> WeaponVec = {};
	Samy* samy;
	int cpt_weapon = 0;
	int _mode;
	Samy* younes;
	std::chrono::steady_clock::time_point temps_fin;
	int killed;
	SDL_Texture* background_im;
};

#endif
