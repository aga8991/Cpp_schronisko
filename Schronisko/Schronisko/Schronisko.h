#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Klient.h"
#include "Kot.h"
#include "Pies.h"

class Schronisko
{
	std::vector<Pies> pieski;
	std::vector<class Kot>	kotki;
public:
	Schronisko();
	void	dodaj_zwierzaka();
	void	stworz_zwierze();
	void	dodaj_zwierzaki_z_pliku();
	void	wyswietl_zwierzaki();
	int		ile_psow() { return pieski.size(); }
	int		ile_kotow() { return kotki.size(); }
	bool	zgodnosc_cech(Pies _pies, Klient<Pies> obecny_klient);
	bool	zgodnosc_cech(Kot _kot, Klient<Kot> obecny_klient);
	void	rozstrzygnij_prosbe(Klient<Pies> &obecny_klient, Pies &_potencjalny);
	void	rozstrzygnij_prosbe(Klient<Kot> &obecny_klient, Kot &_potencjalny);
	Pies	oddaj_psa(int _nr_zwierza) { return pieski.at(_nr_zwierza); };
	Kot		oddaj_kota(int _nr_zwierza) { return kotki.at(_nr_zwierza); };
	void	wez_zwierze(Pies *_oddane);
	void	wez_zwierze(Kot *_oddane);
};



