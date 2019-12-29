#include "../lib/game.hh"
#include <SDL2/SDL_ttf.h>
SDL_Texture* background_im;
Terrain* terrain1 = new Terrain("./images/background1.gif");

Uint32 timeStart = SDL_GetTicks();

int killed = 0;

const int LEVEL_HEIGHT = 400;
const int LEVEL_WIDTH = 1000;
//const int difficulty = 500;

Game::Game(){

}

Game::~Game(){

}



void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int mode){
	//TTF_Init();
	_mode=mode;
	int flags = 0;
	if (_mode == 2)
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
	if (_mode==3) {
		samy = new Samy(450, LEVEL_HEIGHT,1);
		samy->setPicture(renderer);
		younes = new Samy(450+50, LEVEL_HEIGHT,2);
		younes->setPicture(renderer);
		Players.push_back(younes);
		Players.push_back(samy);
	}
	else{
		Samy* player_samy = new Samy(450, LEVEL_HEIGHT,1);
		player_samy->setPicture(renderer);
		//v.push_back(player_samy); // on ajoute Samy à la liste des personnages existants dans le jeu
		samy = player_samy;
		//player_im = SDL_CreateTextureFromSurface(renderer, player_samy->getSurface());
		//SDL_Surface* tmpsurface = IMG_Load("./images/samy.png");
		//player = SDL_CreateTexture4FromSurface(renderer, tmpsurface);
		//SDL_FreeSurface(tmpsurface);
		//player_samy->freeS();
	}
	// Fin de la création
}

void Game::handleEvents(){
	SDL_Event event;
	SDL_PollEvent(&event);
	if (_mode==3) {
		switch(event.type){
			case SDL_QUIT:
				isrunning = false;
				//std::cout <<"quit"<<std::endl;
				break;
			case SDL_KEYDOWN:
				for (auto a: Players) {
					a->update(event, renderer);
				}
			case SDL_KEYUP:
			for (auto a: Players) {
				a->update(event, renderer);
			}
			}
		}
	else{
		switch(event.type){
			case SDL_QUIT:
				isrunning = false;
				//std::cout <<"quit"<<std::endl;
				break;
			case SDL_KEYDOWN:
				samy->update(event, renderer);
			case SDL_KEYUP:
				samy->update(event, renderer);
		}
	}
}

void Game::generateSmoke(){
	double x = rand()%800 +1;
	while( x > 200 && x < LEVEL_WIDTH-200){
		x = rand()%LEVEL_WIDTH +1;
	}
	if(SDL_GetTicks() - timeStart > _difficulty){ // générer un Smoke toutes les 5 secondes
		timeStart = SDL_GetTicks();
		Smoke* s = new Smoke(x, LEVEL_HEIGHT);
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
	 /*TTF_Font *font;
	 font=TTF_OpenFont("angelina.ttf", 16);
	 SDL_Color color={230,230,230};
	 SDL_Surface* text = TTF_RenderText_Solid(font,std::to_string(killed).c_str(), color);
	 SDL_Texture * texture_text = SDL_CreateTextureFromSurface(renderer, text);
	 int texW = 100;
	 int texH = 250;
	 SDL_QueryTexture(texture_text, NULL, NULL, &texW, &texH);
	 SDL_Rect dstrect = { 159, 450, texW, texH };
	 SDL_RenderCopy(renderer, texture_text, NULL, &dstrect);


	  SDL_Surface *texte = NULL;*/

TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size
SDL_Color White = {0,0,0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, std::to_string(killed).c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

SDL_Rect Message_rect; //create a rect
Message_rect.x = 46;  //controls the rect's x coordinate
Message_rect.y = 535; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect


SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}


void Game::update(){
	if(_mode==3 and Players.size()>1){
		for (auto a: Players) {
			a->update();
		}
		bool continuer=false;
		std::cout << "ca marche" << std::endl;
		for (auto a: Players) {
			if (a->estVivant()) {
				continuer=true;
			}
		}
		if(continuer){
			if (smokeVec.size() <= 10)
			{
				this->generateSmoke(); // ajouter un smoke mais pas plus de 10
			}
			for (auto a: Players) {

				if(a->getIsfiring()==true && bulletVec.size() <= 10 + 5*a->getIdWeapon()){
					Bullet* b;
					if(a->getRight()){
						b=new Bullet(a->getX(),a->getY(), a->getIdWeapon());
					}else{
						b=new Bullet(a->getX(),a->getY(),a->getIdWeapon(), 1);
					}
					b->setTrue();
					bulletVec.push_back(b);
					a->setIsfiring(false);
				}
		}
			//std::cout << bulletVec.size() << std::endl;
			//int i = 0;
			std::cout << "ca marche3" << std::endl;
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
					smokeVec[i]->update(samy,younes,renderer);
				}else{
					delete smokeVec[i];
					killed += 1;
				}
			}
			smokeVec = smokeVec_alive;
			if (killed > 10 && WeaponVec.size() == 0 && cpt_weapon == 0)
			{
				Bazooka* bazooka = new Bazooka(rand()%800 +1, LEVEL_HEIGHT);
				WeaponVec.push_back(bazooka);
				cpt_weapon += 1;
			}else if (killed > 35 && WeaponVec.size() == 0 && cpt_weapon == 1)
			{
				DragonBall* d = new DragonBall(rand()%800 +1, LEVEL_HEIGHT);
				WeaponVec.push_back(d);
				cpt_weapon += 1;
			}
			for (auto a: Players) {
				this->weaponupdate(a);
			}
	}
			else {
			isrunning = false;
		}
}

	else{
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
			Bazooka* bazooka = new Bazooka(rand()%800 +1, LEVEL_HEIGHT);
			WeaponVec.push_back(bazooka);
			cpt_weapon += 1;
		}else if (killed > 35 && WeaponVec.size() == 0 && cpt_weapon == 1)
		{
			DragonBall* d = new DragonBall(rand()%800 +1, LEVEL_HEIGHT);
			WeaponVec.push_back(d);
			cpt_weapon += 1;
		}
		this->weaponupdate(samy);
	}else{
		isrunning = false;
	}
}
}


void Game::setHealthStamina(){

	// stamina bar

	SDL_Rect r;
    r.x = 15;
    r.y = 15;
    r.w = 400;
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
    r.w = 400;
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
	this->setScore();
	//this->setText();
	for(auto perso : smokeVec){
		SDL_RenderCopy(renderer, perso->getTexture(), NULL, &perso->getdestR()); // copier tout les 'smokes' dans la liste de smokes
	}
	if(_mode==3){
	SDL_RenderCopy(renderer, samy->getTexture(), NULL, &samy->getdestR()); // placer Samy
	SDL_RenderCopy(renderer, younes->getTexture(), NULL, &younes->getdestR()); // placer Younes
	}
	else{
		SDL_RenderCopy(renderer, samy->getTexture(), NULL, &samy->getdestR()); // placer Samy
	}
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
	if (_mode==3) {
		delete samy;
		delete younes;
	}
	else{
	delete samy;
}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//TTF_CloseFont(font);
	//TTF_Quit();
	SDL_Quit();
	std::cout << "fin " << killed << std::endl;
}
