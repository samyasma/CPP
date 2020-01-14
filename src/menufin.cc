#include "../lib/menufin.hh"
#include <fstream>

SDL_Texture* background_im3;



MenuFin::MenuFin(){

}

MenuFin::~MenuFin(){
	std::cout << "~MenuFin" << std::endl;
}

void MenuFin::init(const char* title, int x, int y, int width, int height, bool fullscreen,int death){
	int flags = 0;
	killed=death;
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
		SDL_Surface* surface = IMG_Load("./images/menu2.png");
		background_im3 = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
}

int MenuFin::handleEvents(){
	int i = 0;
	SDL_Event event;
	SDL_PollEvent(&event);
	int x, y;
	switch(event.type){
		case SDL_QUIT:
			isrunning = false;
			i = 4;
			break;
		case SDL_MOUSEBUTTONDOWN:
		 	SDL_BUTTON(SDL_GetMouseState(&x, &y));
			std::cout << x << " ; " << y << std::endl;
			if (x >= 402 && x <= 774 && y <=96 && y >= 53) //Play Again
			{
				i = 1;
			}
			else if(x >= 402 && x <= 774 && y <=126 && y >= 98){ // support us
				i = 2;
			}
			else if(x >= 274 && x <= 774 && y <=492 && y >= 472){ //soviet mode
				i=3;
			}
	}
	return i;
}
void MenuFin::setBestScore(){
	std::ifstream input("src/best_scores.txt");
	int best_score;
	input >> best_score;
	std::ofstream output("best_scores.txt");
	if (killed>best_score) {
		output << killed;
		best_score=killed;
	}
	else{
		output << best_score;
	}

	if(TTF_Init()<0){ //init ttf pour l'écriture
	   fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
	   exit(EXIT_FAILURE);
	  }
int fontsize = 20;
int t_width = 0; // width of the loaded font-texture
int t_height = 0; // height of the loaded font-texture
SDL_Color text_color = {255,100,100};
std::string fontpath = "src/OpenSans-Bold.ttf";
std::string text = "Best Score is :  "+std::to_string(best_score);
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
int x = 82;
int y = 103;
SDL_Rect dst = {x, y, t_width, t_height};
SDL_RenderCopy(renderer, ftexture, NULL, &dst);

}
void MenuFin::setKill(){
	this->setBestScore();
	if(TTF_Init()<0){ //init ttf pour l'écriture
	   fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
	   exit(EXIT_FAILURE);
	  }
int fontsize = 20;
int t_width = 0; // width of the loaded font-texture
int t_height = 0; // height of the loaded font-texture
SDL_Color text_color = {255,255,255};
std::string fontpath = "src/OpenSans-Bold.ttf";
std::string text = std::to_string(killed);
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
int x = 269;
int y = 53;
SDL_Rect dst = {x, y, t_width, t_height};
SDL_RenderCopy(renderer, ftexture, NULL, &dst);

}




void MenuFin::update(){

}

void MenuFin::render(){
	SDL_RenderClear(renderer);
	// disposition des objets A JOUR, toujours mettre le background au début
	SDL_RenderCopy(renderer, background_im3, NULL, NULL); // placer le background
	this->setKill();
	SDL_RenderPresent(renderer);
}

void MenuFin::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "fin " << std::endl;
}
