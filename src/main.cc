#include <iostream>
#include "../lib/personnage.hh"
#include "../lib/game.hh"
Game *game = nullptr;

int main(int argc, char const *argv[])
{
	game = new Game();
	//game->init("test", 0,0,1000,1000, false);
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