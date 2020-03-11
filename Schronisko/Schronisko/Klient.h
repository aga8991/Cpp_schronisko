#pragma once
#include <iostream>
#include "Pies.h"
#include "Kot.h"

template <typename T>
class Klient
{
	T*			zwierze;
	bool		chec_adopcji;
	bool		posiada_inne_zwierzeta;
	bool		uczulenie;
	std::string jaka_rasa;

public:
	Klient(int _ilosc_zwierzat, bool _uczulenie);
	Klient(T &_zwierze);
	bool		czy_adoptuje() { return chec_adopcji; }
	bool		czy_sa_inne_zwierzeta() { return posiada_inne_zwierzeta; }
	bool		czy_ma_uczulenie() { return uczulenie; }
	std::string jakiej_rasy_szuka() { return jaka_rasa; }
	T*			oddaj_zwierze() { return zwierze; }
	void		wez_zwierze(T* zwierz);
};


//Konstruktor klienta, który chce adoptowaæ
template <typename T>
Klient<T>::Klient(int _ilosc_zwierzat, bool _uczulenie)
{
	zwierze = nullptr;
	chec_adopcji = true;
	uczulenie = _uczulenie;
	if (_ilosc_zwierzat == 0) posiada_inne_zwierzeta = false;
	else posiada_inne_zwierzeta = true;
	int odp;

	do {
		std::cout << "Czy klient szuka konkretnej rasy?\n1. tak\n2. nie" << std::endl;
		std::cin >> odp;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		switch (odp)
		{
		case 1:
			std::cout << "Nazwa rasy: ";
			std::cin >> jaka_rasa;
			break;
		case 2:
			jaka_rasa = "obojetnie";
			break;
		}
	} while (odp < 0 && odp > 2);
}


//Konstruktor klienta, który chce oddaæ zwierzaka
template <typename T>
Klient<T>::Klient(T &_zwierze)
{
	chec_adopcji = false;			//cechy = false, bo sa nieistotne, gdy klient nie adoptuje
	posiada_inne_zwierzeta = false;
	uczulenie = false;
	zwierze = &_zwierze;
}

template<typename T>
void Klient<T>::wez_zwierze(T* zwierz)
{
	zwierze = zwierz;
	std::cout << "Adopcja sie powiodla! :) ";
}