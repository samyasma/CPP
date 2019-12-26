#include <iostream>
#include "../lib/personnage.hh"
#include "../lib/game.hh"


Game *game = nullptr;

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	game = new Game();
	game->init("Smoke v1.0", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600, false);

	Uint32 frameStart; // gestion des frames
	int frameTime;

	while(game->running()){
		frameStart = SDL_GetTicks();
		std:: cout << "handle" << std::endl;
		game->handleEvents(); // Handle any user input
		std:: cout << "update" << std::endl;
		game->update(); // update all objects
		std:: cout << "render" << std::endl;
		game->render(); // render changes to the display
		std:: cout << "fin" << std::endl;

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay-frameTime);
		}
		// Pourquoi tout ça ?? pour rendre les déplacements plus smooth !!

	}

	game->clean();
	return 0;
}
