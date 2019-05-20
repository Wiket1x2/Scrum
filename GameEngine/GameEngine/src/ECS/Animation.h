#pragma once
struct Animation
{
	int index; //indeksowanie
	int frame; //ilosc klatek animacji
	int speed; //szybkosc animacji
	
	Animation() {}

	Animation(int i, int f, int s) //przyjmuje trzy wartosci calkowite: i,f,s - odpowiednio przypisuje je do indeksu, liczby klatek i czasu wyswietlania
	{
		index = i;
		frame = f;
		speed = s;
	}
};