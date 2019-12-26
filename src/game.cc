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
			samy->update(event, renderer);
		case SDL_KEYUP:
			samy->update(event, renderer);
	}
}

void Game::generateSmoke(){
	double x = rand()%800 +1;
	if(SDL_GetTicks() - timeStart> 5000){ // générer un Smoke toutes les 5 secondes
		timeStart = SDL_GetTicks();
		Smoke* s = new Smoke(x, 400);
		s->setPicture(renderer);
		smokeVec.push_back(s);
	}
}


void Game::update(){
	samy->update(); // gestion du saut
	if (smokeVec.size() <= 10)
	{
		this->generateSmoke(); // ajouter un smoke mais pas plus de 10
	}
	if(samy->getIsfiring()==true && bulletVec.size() <= 10){
		Bullet* b;
		if(samy->getRight()){
			b=new Bullet(samy->getX(),samy->getY());
		}else{
			b=new Bullet(samy->getX(),samy->getY(), 1);	
		}
		b->setTrue();
		bulletVec.push_back(b);
		samy->setIsfiring(false);
	}
	std::cout << bulletVec.size() << std::endl;
	//int i = 0;
	std::vector<Bullet*> bulletVec_temp = {};
	for(auto a:  bulletVec){
		//std:: cout << "peut etre ici 1" << std::endl;
		if(a != nullptr){
			if (a->getB())
			{
				a->update(renderer);
				bulletVec_temp.push_back(a);
			}else{
				//std::cout << "hi" << std::endl;
				delete a;
			}
		}
	}
	bulletVec = bulletVec_temp;
	for (size_t i = 0; i < smokeVec.size(); i++) {
		for (auto blt: bulletVec){
			if(blt != nullptr){
				smokeVec[i]->CheckCollsion(blt);
			}
		}
		smokeVec[i]->update();
	}

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
	SDL_RenderCopy(renderer, background_im, NULL, NULL); // placer le background
	this->setHealthStamina(); // placer les barres de health et stamina
	//this->setText();
	for(auto perso : smokeVec){
		SDL_RenderCopy(renderer, perso->getTexture(), NULL, &perso->getdestR()); // copier tout les 'smokes' dans la liste de smokes
	}
	SDL_RenderCopy(renderer, samy->getTexture(), NULL, &samy->getdestR()); // placer Samy
	for (auto a:  bulletVec){
		SDL_RenderCopy(renderer, a->getTexture(), NULL, &a->getdestR()); // afficher la bullet
	}
	SDL_RenderPresent(renderer); // afficher le render
}

void Game::clean(){
	for (auto p : smokeVec)
	{
		delete p;
	}
	for (auto a : bulletVec)
	{
		delete a;
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "fin" << std::endl;
}
