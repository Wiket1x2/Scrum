#include "game.h"

Game *game = nullptr; //tworzymy zerowy wskaznik na Game

int main(int argc, char *argv[])  //wyglad fukncji main w VS dla bibliotek
{
	const int FPS = 60; //tworzymy stala zmienna ktora przechowuje ilosc klatek per sec (60-optimum)
	const int frameDelay = 1000 / FPS; //czas na obliczenie 1 klatki (1000ms/60 frames)

	Uint32 frameStart; //32-bit zmienna 
	int frameTime; 

	game = new Game(); //wskaznikowi przypisujemy pamiec na obiekt game

	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 1024, false); //wywolujemy funckje init z obiektu game - przyjmuje nazwe, pozycje na erkanie , szerokosc okna , true/false - fullscreen

	while (game->running()) //nieskonczona petla - nasz program : jesli isrunnng==True
	{
		frameStart = SDL_GetTicks(); //zaczyna liczyc czas

		game->handleEvents(); //spr czy cos sie stalo
		game->update(); //nadpisuje klasy
		game->render(); //wystietla na ekranie

		frameTime = SDL_GetTicks() - frameStart; //roznica czasowa: czas trwania wywolania funkcji z game

		if (frameDelay > frameTime) //warunek ustalajacy ilosc klatek/ opoznienie
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean(); //czysci pamiec itd...

	return 0;
}