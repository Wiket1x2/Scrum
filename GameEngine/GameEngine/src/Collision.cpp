#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) //opisuje kwadraty w poczatku: lewy gorny rog
{
	if (
		recA.x + recA.w >= recB.x && //x,y -wspolrzedne w-szerokosc, h-wysokosc kwadratu -> sprawdza czy warunki kolizji sa spelnione (patrz parametry-x,y,w,h)
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true; //true - kwadraty ze soba koliduja
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit: " << colB.tag << std::endl; 
		//jesli wystepuje kolizja zwraca true i wyswietla hit z parametrami
		return true;
	}
	else
	{
		return false;
	}
}