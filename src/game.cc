#include "../lib/game.hh"

SDL_Texture* background_im;
Terrain* terrain1 = new Terrain("./images/background1.gif");

Uint32 timeStart = SDL_GetTicks();

int killed = 0;

//const int difficulty = 500;

Game::Game(){

}

Game::~Game(){

}



void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int difficulty){
	//TTF_Init();
	int flags = 0;
	if (difficulty == 2)
	{
		_difficulty = 500;
	}else{
		_difficulty = 3000;
	}
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
	Samy* player_samy = new Samy(300, 400);
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
	while( x > 200 && x < 600){
		x = rand()%800 +1;
	}
	if(SDL_GetTicks() - timeStart > _difficulty){ // générer un Smoke toutes les 5 secondes
		timeStart = SDL_GetTicks();
		Smoke* s = new Smoke(x, 400);
		s->setPicture(renderer);
		smokeVec.push_back(s);
	}
}

void Game::weaponupdate(Samy* samy){
	for (auto a : WeaponVec)
	{
		a->update(this->renderer);
		if (a->update(samy))
		{
			delete a;
			WeaponVec = {};
		}
	}
}

void Game::setScore(){
	// SDL_Surface* text = TTF_RenderText_Solid(font,std::to_string(killed).c_str(), color);
	// SDL_Texture * texture_text = SDL_CreateTextureFromSurface(renderer, text);
	// int texW = 0;
	// int texH = 0;
	// SDL_QueryTexture(texture_text, NULL, NULL, &texW, &texH);
	// SDL_Rect dstrect = { 0, 0, texW, texH };
	// SDL_RenderCopy(renderer, texture_text, NULL, &dstrect);
}


void Game::update(){
	samy->update(); // gestion du saut
	unsigned int id_balle = samy->getIdWeapon();
	if(samy->estVivant()){
		if (smokeVec.size() <= 10)
		{
			this->generateSmoke(); // ajouter un smoke mais pas plus de 10
		}
		if(samy->getIsfiring()==true && bulletVec.size() <= 10 + 5*id_balle){
			Bullet* b;
			if(samy->getRight()){
				b=new Bullet(samy->getX(),samy->getY(), id_balle);
			}else{
				b=new Bullet(samy->getX(),samy->getY(),id_balle, 1);	
			}
			b->setTrue();
			bulletVec.push_back(b);
			samy->setIsfiring(false);
		}
		//std::cout << bulletVec.size() << std::endl;
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
		std::vector<Smoke*> smokeVec_alive = {};
		for (size_t i = 0; i < smokeVec.size(); i++) {
			for (auto blt: bulletVec){
				if(blt != nullptr){
					smokeVec[i]->CheckCollsion(blt);
				}
			}
			smokeVec[i]->update();
			if(smokeVec[i]->estVivant()){
				smokeVec_alive.push_back(smokeVec[i]);
				smokeVec[i]->update(samy, renderer);
			}else{
				delete smokeVec[i];
				killed += 1;
			}
		}
		smokeVec = smokeVec_alive;
		if (killed > 10 && WeaponVec.size() == 0 && cpt_weapon == 0)
		{
			Bazooka* bazooka = new Bazooka(rand()%800 +1, 400);
			WeaponVec.push_back(bazooka);
			cpt_weapon += 1;
		}else if (killed > 35 && WeaponVec.size() == 0 && cpt_weapon == 1)
		{
			DragonBall* d = new DragonBall(rand()%800 +1, 400);
			WeaponVec.push_back(d);
			cpt_weapon += 1;
		}
		this->weaponupdate(samy);
	}else{
		isrunning = false;
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
	for (auto w:  WeaponVec){
		SDL_RenderCopy(renderer, w->getTexture(), NULL, &w->getdestR()); // afficher la bullet
	}
	//this->setScore();
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
	for (auto w : WeaponVec)
	{
		delete w;
	}
	delete samy;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//TTF_CloseFont(font);
	//TTF_Quit();
	SDL_Quit();
	std::cout << "fin " << killed << std::endl;
}
