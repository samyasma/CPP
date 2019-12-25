#include "../lib/game.hh"

SDL_Texture* player_im; //juste pour le test, à supprimer plus tard
SDL_Rect srcR, destR; 

SDL_Texture* background_im;
Terrain* terrain1 = new Terrain("./images/background1.gif");


Game::Game(){

}

Game::~Game(){

}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen){
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialisation ok" << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window)
		{
			std::cout << "la fenetre a bien ete créée " << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer ok" << std::endl;
		}

		isrunning = true;
	}
	background_im = SDL_CreateTextureFromSurface(renderer, terrain1->getSurface());
	Personnage* player_samy = new Personnage(0,0,100,100, "./images/samy.png");
	v.push_back(player_samy); // on ajoute Samy à la liste des personnages existants dans le jeu
	player_im = SDL_CreateTextureFromSurface(renderer, player_samy->getSurface());
	//SDL_Surface* tmpsurface = IMG_Load("./images/samy.png");
	//player = SDL_CreateTextureFromSurface(renderer, tmpsurface);
	//SDL_FreeSurface(tmpsurface);
	player_samy->freeS();
}

void Game::handleEvents(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			isrunning = false;
			break;
		default:
			break;
	}
}

void Game::update(){
	destR.w = 128;
	destR.h = 128;
}

void Game::render(){
	SDL_RenderClear(renderer);
	// création des objets etc
	SDL_RenderCopy(renderer, background_im, NULL, NULL);
	SDL_RenderCopy(renderer, player_im, NULL, &destR);
	SDL_RenderPresent(renderer);
}

void Game::clean(){
	for (auto p : v)
	{
		delete p;
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "fin" << std::endl;
}
