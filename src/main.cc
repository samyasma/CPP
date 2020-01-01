#include <iostream>
#include "../lib/personnage.hh"
#include "../lib/game.hh"
#include "../lib/menu.hh"
#include "../lib/menufin.hh"
#include <SFML/Audio.hpp>
#include <chrono>

Game *game = nullptr;
Menu* menu = nullptr;
MenuFin* menufin=nullptr;

void run(int i, const int frameDelay,bool soviet_mode){
	game = new Game();
	game->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600, false, i,soviet_mode);
	Uint32 frameStart; // gestion des frames
	int frameTime;
	std::chrono::steady_clock::time_point tend = std::chrono::steady_clock::now()
																						 + std::chrono::seconds(120);
	//while(game->running()){
  while (std::chrono::steady_clock::now() < tend && game->running())
    {
		frameStart = SDL_GetTicks();
		std:: cout << "handle" << std::endl;
		game->handleEvents(); // Handle any user input
		std:: cout << "update" << std::endl;
		game->update(); // update all objects
		std:: cout << "render" << std::endl;
		game->render(); // render changes to the display
		//std:: cout << "fin" << std::endl;

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay-frameTime);
		}
		// Pourquoi tout ça ?? pour rendre les déplacements plus smooth !!
	}
	game->clean();
	delete game;
	std::cout << "fin game" << std::endl;
}

int main(int argc, char const *argv[])
{
	sf::Music music;
	if (!music.openFromFile("/home/samy/Bureau/MAIN4/C++/projet/CPP/src/aristocrate.ogg")){
    std::cerr << "ERROR" << std::endl;; // error
	}
	music.play();
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	menu = new Menu();
	menufin=new MenuFin();
	menu->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600, false);
	//bool activate = false;
	int i = 0;
	while(menu->running()){
		i = menu->handleEvents();
		menu->update();
		menu->render();
		if(i==3 || i == 2 || i == 1){
			run(i, frameDelay,false);
			break;
		}
	}
	menu->clean();
	delete menu;
	menufin->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600, false);
	int j=0;
	while(menufin->running()){
		j = menufin->handleEvents();
		menufin->update();
		menufin->render();
		if(j==3){
			run(i, frameDelay,true);
			break;
		}
		if (j==1) {
			run(i, frameDelay,false);
			break;
		}
	}
	menufin->clean();
	delete menufin;
	return 0;
}
