#pragma once
#include <string>
#include "Zwierze.h"

class Kot : public Zwierze
{
	int		kot_domowy;
	int		nr_w_schronisku;

public:
	Kot();
	Kot(std::string _imie_kota, int _agresja_kota, std::string _rasa_kota, int _domowy, int _nr = 0);
	int		_czy_kot_jest_domowy() { return kot_domowy; }
	int		jaki_numer() { return nr_w_schronisku; }
	void	nadaj_nr(int _nr) { nr_w_schronisku = _nr; }
	bool	mozliwy_atak();		// polimorfim
};


