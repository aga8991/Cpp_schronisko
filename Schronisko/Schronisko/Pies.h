#pragma once
#include <iostream>
#include <string>
#include "Zwierze.h"

class Pies : public Zwierze
{
	int		wielkosc;	//1-ma³y, 2-œredni, 3-du¿y
	bool	uczulajacy;
	int		nr_w_schronisku;

public:
	Pies();
	Pies(std::string _imie_psa, int _agresja_psa, std::string _rasa_psa, int _wielkosc, bool _uczula, int _nr = 0);
	bool	czy_uczula() { return uczulajacy; }
	int		jak_duzy() { return wielkosc; }
	int		jaki_numer() { return nr_w_schronisku; }
	void	nadaj_nr(int _nr) { nr_w_schronisku = _nr; }
	bool	mozliwy_atak();		// polimorfizm
};



