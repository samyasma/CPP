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
	samy->update();
	if (v.size() <= 10)
	{
		this->generateSmoke();
	}
}

void Game::setText(){
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

	SDL_Color Black = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "STAMINA", Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 20;  //controls the rect's x coordinate 
	Message_rect.y = 405; // controls the rect's y coordinte
	Message_rect.w = 50; // controls the width of the rect
	Message_rect.h = 20; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	SDL_FreeSurface(surfaceMessage);
	//SDL_FreeTexture(Message);
}

void Game::setHealthStamina(){

	// stamina bar

	SDL_Rect r;
    r.x = 15;
    r.y = 15;
    r.w = 200;
    r.h = 20;
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderFillRect(renderer, &r);
    SDL_Rect r2;
    r2.x = 15;
    r2.y = 15;
    if(double(samy->getStamina()/100.0) >= 0){
    	r2.w = 200.0*double(samy->getStamina()/100.0);
    }else{
    	r2.w = 0;
    }
    r2.h = 20;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 155);
    SDL_RenderFillRect(renderer, &r2);

    // health bar

    r.x = 15;
    r.y = 40;
    r.w = 200;
    r.h = 20;
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderFillRect(renderer, &r);
    r2.x = 15;
    r2.y = 40;
    if(double(samy->getVie()/100.0) >= 0){
    	r2.w = 200.0*double(samy->getVie()/100.0);
    }else{
    	r2.w = 0;
    }
    r2.h = 20;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 155);
    SDL_RenderFillRect(renderer, &r2);

    // il manque les images

}

void Game::render(){
	SDL_RenderClear(renderer);
	// disposition des objets A JOUR, toujours mettre le background au début
	SDL_RenderCopy(renderer, background_im, NULL, NULL);
	this->setHealthStamina();
	this->setText();
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
