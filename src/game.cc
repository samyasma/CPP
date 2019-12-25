#include "../lib/game.hh"

//SDL_Texture* player_im; //juste pour le test, à supprimer plus tard
//SDL_Rect srcR, destR; 

SDL_Texture* background_im;
Terrain* terrain1 = new Terrain("./images/background1.gif");

Uint32 timeStart = SDL_GetTicks();


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

	// Création du fond ainsi que du personnage principal voir la vidéo pour comprendre comment ça marche


	background_im = SDL_CreateTextureFromSurface(renderer, terrain1->getSurface());

	Samy* player_samy = new Samy(100, 400);
	player_samy->setPicture(renderer);
	//v.push_back(player_samy); // on ajoute Samy à la liste des personnages existants dans le jeu
	samy = player_samy;

	//player_im = SDL_CreateTextureFromSurface(renderer, player_samy->getSurface());
	//SDL_Surface* tmpsurface = IMG_Load("./images/samy.png");
	//player = SDL_CreateTextureFromSurface(renderer, tmpsurface);
	//SDL_FreeSurface(tmpsurface);
	//player_samy->freeS();

	// Fin de la création
}

void Game::handleEvents(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			isrunning = false;
			break;
		case SDL_KEYDOWN:
			samy->update(event);
		default:
			break;
	}
}

void Game::generateSmoke(){
	double x = rand()%800 +1;
	if(SDL_GetTicks() - timeStart> 5000){ // générer un Smoke toutes les 5 secondes
		timeStart = SDL_GetTicks();
		Smoke* s = new Smoke(x, 400);
		s->setPicture(renderer);
		v.push_back(s);
	}
}

void Game::update(){
	if (v.size() <= 10)
	{
		this->generateSmoke();
	}
		
	// for(auto p : v){
	// 	destR.w = 128;
	// 	destR.h = 128;
	// 	destR.x = p->getX();
	// 	destR.y = p->getY();
	// }
}

void Game::render(){
	SDL_RenderClear(renderer);
	// disposition des objets A JOUR, toujours mettre le background au début
	SDL_RenderCopy(renderer, background_im, NULL, NULL);
	for(auto perso : v){
		SDL_RenderCopy(renderer, perso->getTexture(), NULL, &perso->getdestR());
	}
	SDL_RenderCopy(renderer, samy->getTexture(), NULL, &samy->getdestR());
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
