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

int  run(int i, const int frameDelay,bool soviet_mode){
	game = new Game();
	game->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600, false, i,soviet_mode);
	Uint32 frameStart; // gestion des frames
	int frameTime;
	std::chrono::steady_clock::time_point tend = std::chrono::steady_clock::now()+ std::chrono::seconds(120);
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
	int mort;
	mort=game->getKilled();
	game->clean();
	delete game;
	std::cout << "fin game" << std::endl;
	return mort;
}

int main(int argc, char const *argv[])
{
	sf::Music music1;
	sf::Music music2;
	if (!music1.openFromFile("src/aristocrate.ogg")){
    	std::cerr << "ERROR" << std::endl;; // error
	}
	if (!music2.openFromFile("src/URSS.ogg")){
		std::cerr << "ERROR" << std::endl;; // error
	}
	music1.play();
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	menu = new Menu();
	menufin=new MenuFin();
	int mort;
	menu->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600, false);
	//bool activate = false;
	int i = 0;
	while(menu->running()){
		i = menu->handleEvents();
		menu->update();
		menu->render();
		if(i==3 || i == 2 || i == 1){
			mort=run(i, frameDelay,false);
			break;
		}
	}
	menu->clean();
	delete menu;

	// menu fin
	int party=0;
	while (menufin->running() && party<5) {

	menufin->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600, false,mort);
	int j=0;
	while(menufin->running()){
		j = menufin->handleEvents();
		if (j == 4)
		{
			menufin->clean();
			break;
		}
		menufin->update();
		menufin->render();
		if(j==3){
			music1.pause();
			music2.play();
			mort=run(i, frameDelay,true);
			break;
		}
		if (j==1) {
			music2.pause();
			music1.play();
			mort=run(i, frameDelay,false);
			break;
		}
	}
	menufin->clean();
	if(j != 4){
		menufin=nullptr;
		menufin=new MenuFin();
	}
	party+=1;
}
	delete menufin;
	return 0;
}
