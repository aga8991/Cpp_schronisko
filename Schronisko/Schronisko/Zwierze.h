#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

class Zwierze
{
protected:
	std::string imie;
	int poziom_agresji;		//od 1 do 10
	std::string rasa;
public:
	Zwierze() :poziom_agresji(0) { imie[0] = '0'; rasa[0] = '0'; };
	int jaka_agresja() { return poziom_agresji; }
	std::string jakie_imie() { return imie; }
	std::string jaka_rasa() { return rasa; }
	virtual bool mozliwy_atak() = 0;
};