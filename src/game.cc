#include "../lib/game.hh"
#include <SDL2/SDL_ttf.h>
#include <SFML/Audio.hpp>

Uint32 timeStart = SDL_GetTicks();


const int LEVEL_HEIGHT = 400;
const int LEVEL_WIDTH = 1000;
//const int difficulty = 500;

Game::Game(){

}

Game::~Game(){
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
}

bool Game::running(){
	return isrunning;
}

int Game::getKilled(){
	return killed;
}

std::vector<Smoke*> Game::getListSmoke(){
	return smokeVec;
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen, unsigned int mode, bool soviet_mode){
	killed=0; // nombre de mort
	temps_fin=std::chrono::steady_clock::now() + std::chrono::seconds(120); // Timer
	Terrain* terrain1 = new Terrain("./images/background1.gif"); //Mise en place du terrain
	_mode=mode; //Le mode désigne la difficulté Easy ou Hard ou multiplayer
	int flags = 0;
	//Ici on decide de la difficulté du jeu
	if (_mode == 2)
	{
		_difficulty = 2000;
	}else{
		_difficulty = 6000;
	}
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
 //Initialisation de la fenetre graphique
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

	// Si le soviet mode est true, on change de background

	if (soviet_mode) {
		terrain1= new Terrain("./images/background2.png");
		_difficulty = 500;
	}
	background_im = SDL_CreateTextureFromSurface(renderer, terrain1->getSurface());
// le mode 3 est le mode multipjoueur
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
		samy = player_samy;

	}
	// Fin de la création
}
// Permet de gérer les evenements claviers
void Game::handleEvents(){
	SDL_Event event;
	SDL_PollEvent(&event);
	if (_mode==3) { //cas multiplayer
		switch(event.type){
			case SDL_QUIT:
				isrunning = false;
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
		switch(event.type){ //cas joueur unique
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
//////////////SET SCORE///////////////////////
void Game::setScore(){
	if(TTF_Init()<0){ //init ttf pour l'écriture
	   fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
	   exit(EXIT_FAILURE);
	  }
int fontsize = 120;
int t_width = 0; // width of the loaded font-texture
int t_height = 0; // height of the loaded font-texture
SDL_Color text_color = {250,100,88};
std::string fontpath = "src/game_over.ttf";
std::string text ="Kill :"+std::to_string(killed);
TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);
SDL_Texture* ftexture = NULL; // our font-texture

// check to see that the font was loaded correctly
if (font == NULL) {
	 std::cerr << "Failed the load the font!\n";
	 std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
}
else {
	 // now create a surface from the font
	 SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);

	 // render the text surface
	 if (text_surface == NULL) {
			 std::cerr << "Failed to render text surface!\n";
			 std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
	 }
	 else {
			 // create a texture from the surface
			 ftexture = SDL_CreateTextureFromSurface(renderer, text_surface);

			 if (ftexture == NULL) {
					 std::cerr << "Unable to create texture from rendered text!\n";
			 }
			 else {
					 t_width = text_surface->w; // assign the width of the texture
					 t_height = text_surface->h; // assign the height of the texture

					 // clean up after ourselves (destroy the surface)
					 SDL_FreeSurface(text_surface);
			 }
	 }
}
TTF_CloseFont(font);
TTF_Quit();
int x = 30;
int y = 150;
SDL_Rect dst = {x, y, t_width, t_height};
SDL_RenderCopy(renderer, ftexture, NULL, &dst);

}
/////////TIMER:///////////////////////////
void Game::setTimer(){
	if(TTF_Init()<0){ //init ttf pour l'écriture
	   fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
	   exit(EXIT_FAILURE);
	  }
int fontsize = 120;
int t_width = 0; // width of the loaded font-texture
int t_height = 0; // height of the loaded font-texture
SDL_Color text_color = {45,150,88};
std::string fontpath = "src/game_over.ttf";
std::chrono::duration<double> elapsed_seconds=temps_fin-(std::chrono::steady_clock::now());
std::string text = "Timer :"+std::to_string(int(elapsed_seconds.count()));
TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);
SDL_Texture* ftexture = NULL; // our font-texture

// check to see that the font was loaded correctly
if (font == NULL) {
	 std::cerr << "Failed the load the font!\n";
	 std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
}
else {
	 // now create a surface from the font
	 SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);

	 // render the text surface
	 if (text_surface == NULL) {
			 std::cerr << "Failed to render text surface!\n";
			 std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
	 }
	 else {
			 // create a texture from the surface
			 ftexture = SDL_CreateTextureFromSurface(renderer, text_surface);

			 if (ftexture == NULL) {
					 std::cerr << "Unable to create texture from rendered text!\n";
			 }
			 else {
					 t_width = text_surface->w; // assign the width of the texture
					 t_height = text_surface->h; // assign the height of the texture

					 // clean up after ourselves (destroy the surface)
					 SDL_FreeSurface(text_surface);
			 }
	 }
}
TTF_CloseFont(font);
TTF_Quit();
int x = 30;
int y = 90;
SDL_Rect dst = {x, y, t_width, t_height};
SDL_RenderCopy(renderer, ftexture, NULL, &dst);

}


void Game::update(){
	if(_difficulty > 200){
		_difficulty -= 0.0001;
	}
	if(_mode==3 and Players.size()>1){ //Gerer le mode multijoueur
		for (auto a: Players) {
			a->update();
		}
		bool continuer=false;
		//std::cout << "ca marche" << std::endl;
		for (auto a: Players) {
			if (a->estVivant()) {
				continuer=true;
			}
		}
		if(continuer){ //apparition des smokes si le nombre ne depasse pas 10
			if (smokeVec.size() <= 10)
			{
				this->generateSmoke(); // ajouter un smoke mais pas plus de 10
			}
			for (auto a: Players) { //Gerer si quelles sont les joueur qui tire

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

			//Cette section gère la collision entre les bullet et les smoke et les elimine si il sont toucher
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
			//Cette partie gère l'attribution des armes
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
  // Cette partie a les memes fonctionnalité que celle d'en haut sauf quelle est adapté à un joueur unique
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
 /////////////Mode multijoueur///
    if (_mode==3){
			SDL_Rect r3;
		    r3.x = 580;
		    r3.y = 15;
		    r3.w = 400;
		    r3.h = 20;
		    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
		    SDL_RenderFillRect(renderer, &r3);
		    SDL_Rect r4;
		    r4.x = 580;
		    r4.y = 15;
		    if(double(younes->getStamina()/100.0) >= 0){
		    	r4.w = 200.0*double(younes->getStamina()/100.0);
		    }else{
		    	r4.w = 0;
		    }
		    r4.h = 20;
		    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 155);
		    SDL_RenderFillRect(renderer, &r4);

		    // health bar

		    r3.x = 580;
		    r3.y = 40;
		    r3.w = 400;
		    r3.h = 20;
		    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
		    SDL_RenderFillRect(renderer, &r3);
		    r4.x = 580;
		    r4.y = 40;
		    if(double(younes->getVie()/100.0) >= 0){
		    	r4.w = 200.0*double(younes->getVie()/100.0);
		    }else{
		    	r4.w = 0;
		    }
		    r4.h = 20;
		    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 155);
		    SDL_RenderFillRect(renderer, &r4);
		}

}


void Game::render(){
	SDL_RenderClear(renderer);
	// disposition des objets A JOUR, toujours mettre le background au début
	SDL_RenderCopy(renderer, background_im, NULL, NULL); // placer le background
	this->setHealthStamina(); // placer les barres de health et stamina
	this->setScore();
	this->setTimer();
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "fin " << killed << std::endl;
	killed=0;
}
