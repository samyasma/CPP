#include "../lib/menu.hh"

SDL_Texture* background_im2;



Menu::Menu(){

}

Menu::~Menu(){
	std::cout << "~Menu" << std::endl;
}

void Menu::init(const char* title, int x, int y, int width, int height, bool fullscreen){
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
		SDL_Surface* surface = IMG_Load("./images/title.png");
		background_im2 = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
}

int Menu::handleEvents(){
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
			if (x >= 550 && x <= 710 && y <=410 && y >= 360) //hard mode
			{
				i = 2;
			}
			else if(x >= 100 && x <= 300 && y <=410 && y >= 360){
				i = 1;
			}
			else if(x >= 310 && x <= 540 && y <=330 && y >= 280){
				i=3;
			}
	}
	return i;
}

void Menu::update(){

}

void Menu::render(){
	SDL_RenderClear(renderer);
	// disposition des objets A JOUR, toujours mettre le background au début
	SDL_RenderCopy(renderer, background_im2, NULL, NULL); // placer le background
	SDL_RenderPresent(renderer);
}

void Menu::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "fin " << std::endl;
}
