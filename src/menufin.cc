#include "../lib/menufin.hh"

SDL_Texture* background_im3;



MenuFin::MenuFin(){

}

MenuFin::~MenuFin(){
	std::cout << "~MenuFin" << std::endl;
}

void MenuFin::init(const char* title, int x, int y, int width, int height, bool fullscreen){
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
			break;
		case SDL_MOUSEBUTTONDOWN:
		 	SDL_BUTTON(SDL_GetMouseState(&x, &y));
			//std::cout << x << " ; " << y << std::endl;
			if (x >= 402 && x <= 603 && y <=64 && y >= 35) //Play Again
			{
				i = 1;
			}
			else if(x >= 402 && x <= 603 && y <=126 && y >= 98){ // support us
				i = 2;
			}
			else if(x >= 214 && x <= 623 && y <=333 && y >= 303){ //soviet mode
				i=3;
			}
	}
	return i;
}

void MenuFin::update(){

}

void MenuFin::render(){
	SDL_RenderClear(renderer);
	// disposition des objets A JOUR, toujours mettre le background au début
	SDL_RenderCopy(renderer, background_im3, NULL, NULL); // placer le background
	SDL_RenderPresent(renderer);
}

void MenuFin::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "fin " << std::endl;
}
