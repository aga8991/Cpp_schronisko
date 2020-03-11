#include "Kot.h"

Kot::Kot()
{
	nr_w_schronisku = 0;
	kot_domowy = 1;
	imie[0] = '-';
	rasa[0] = '-';
}

Kot::Kot(std::string _imie_kota, int _agresja_kota, std::string _rasa_kota, int _domowy, int _nr)
{
	nr_w_schronisku = _nr;
	imie =  _imie_kota;
	poziom_agresji = _agresja_kota;
	rasa = _rasa_kota;
	kot_domowy = _domowy;
}

bool Kot::mozliwy_atak()
{
	if (poziom_agresji == 0) return false;
	else if (poziom_agresji == 10)
	{
		std::cout << "Kot " << imie << " podrapal potencjalnego wlasciciela i musi zostac w schronisku!" << std::endl;
		system("pause");
		return true;
	}
	else
	{
		int x = rand() % (10 - poziom_agresji);
		if (x == 1)
		{
			std::cout << "Kot "<< imie <<" podrapal potencjalnego wlasciciela i musi zostac w schronisku!" << std::endl;
			system("pause");
			return true;
		}
		else return false;
	}
}