#include "Pies.h"

Pies::Pies()
{
	nr_w_schronisku = 0;
	wielkosc = 1;
	uczulajacy = false;
	imie[0] = '-';
	rasa[0] = '-';
}

Pies::Pies(std::string _imie_psa, int _agresja_psa, std::string _rasa_psa, int _wielkosc, bool _uczula, int _nr)
{
	nr_w_schronisku = _nr;
	imie = _imie_psa;
	poziom_agresji = _agresja_psa;
	rasa =  _rasa_psa;
	wielkosc = _wielkosc;
	uczulajacy = _uczula;
}

bool Pies::mozliwy_atak()
{
	if (poziom_agresji == 0) return false;
	else if (poziom_agresji == 10)
	{
		std::cout << "Pies ugryzl potencjalnego wlasciciela i musi zostac w schronisku!" << std::endl;
		system("pause");
		return true;
	}
	else
	{
		int x = rand() % (10 - poziom_agresji);
		if (x == 1)
		{
			std::cout << "Pies ugryzl potencjalnego wlasciciela i musi zostac w schronisku!" << std::endl;
			system("pause");
			return true;
		}
		else return false;
	}
}