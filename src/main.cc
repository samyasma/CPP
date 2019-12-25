#include <iostream>
#include "../lib/personnage.hh"
#include "../lib/game.hh"
Game *game = nullptr;

int main(int argc, char const *argv[])
{
	game = new Game();
	game->init("test", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600, false);
	//game_is_running = true;
	while(game->running()){

		game->handleEvents();
		game->update();
		game->render();
		//std::cout << "hi" << std::endl;
		// Handle any user input
		// update all objects
		// render changes to the display
	}
	game->clean();
	return 0;
}