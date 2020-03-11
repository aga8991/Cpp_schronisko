#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include "Klient.h"
#include "Schronisko.h"

int		rozgrywka(Schronisko _schronisko);
void	wczytywanie_cyfr_z_konsoli(int& _odp);
void	odpowiedz_zakres(int& _odp, int _poczatek, int _koniec);
void	odpowiedz_string(std::string& _odp);
Pies	wczytaj_z_pliku_psa(Schronisko _schronisko);
Kot		wczytaj_z_pliku_kota(Schronisko _schronisko);
void	stworzenie_klienta(Schronisko *_schronisko);

int main()
{
	srand(time(NULL));
	Schronisko Moje_schronisko;

	if (rozgrywka(Moje_schronisko) == 0) return 0;
}

int rozgrywka(Schronisko _schronisko)
{
	int odp = 0;
	while (1)
	{
		system("cls");
		std::cout << "Co chcesz zrobic teraz?\n1. Dodaj zwierzeta.\n2. Wyswietl swoje zwierzaki.\n3. Przyjmij klienta.\n4. Zakoncz.\n\n Twoja odpowiedz: ";
		odpowiedz_zakres(odp, 1, 4);

		switch (odp)
		{
		case 1:
			_schronisko.dodaj_zwierzaka();
			break;
		case 2:
			_schronisko.wyswietl_zwierzaki();
			break;
		case 3:
			stworzenie_klienta(&_schronisko);
			break;
		case 4:
			return 0;
		}
	}
}

Pies wczytaj_z_pliku_psa(Schronisko _schronisko)
{
	std::ifstream	plik;
	std::string		nazwa_pliku = "Psy.csv";

	plik.open(nazwa_pliku.c_str(), std::ifstream::in);
	if (!plik.fail())
	{
		std::string	wczytywany_wiersz;
		int x = (rand() % 9) + 1;

		for (int i = 0; i < x; i++)
		{
			std::getline(plik, wczytywany_wiersz);    //wczytanie pierwszego wiersza z tytulami
		}

			std::string imie_string, rasa_string, agresywnosc, dodatkowa_cecha, uczulanie;

			std::getline(plik, imie_string, ';');
			std::getline(plik, agresywnosc, ';');
			std::getline(plik, rasa_string, ';');
			std::getline(plik, dodatkowa_cecha, ';');
			std::getline(plik, uczulanie, '\n');

			int agresja = 0;
			char temp[2];
			if (agresywnosc != "10")
			{
				strcpy_s(temp, agresywnosc.c_str());
				agresja = temp[0] - 48;
			}
			else
			{
				agresja = 10;
			}

			strcpy_s(temp, dodatkowa_cecha.c_str());
			int dodatkowa_cecha_int = temp[0] - 48;

			bool uczulony = false;
			if (uczulanie == "tak")
			{
				uczulony = true;
			}
			plik.close();
			Pies nowy_pies(imie_string, agresja, rasa_string, dodatkowa_cecha_int, uczulony);
			return nowy_pies;
	}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
		system("pause");
	}
}

Kot wczytaj_z_pliku_kota(Schronisko _schronisko)
{
	std::ifstream	plik;
	std::string		nazwa_pliku = "Koty.csv";

	plik.open(nazwa_pliku.c_str(), std::ifstream::in);
	if (!plik.fail())
	{
		std::string	wczytywany_wiersz;
		int x = (rand() % 9) + 1;

		for (int i = 0; i < x; i++)
		{
			std::getline(plik, wczytywany_wiersz);    //wczytanie pierwszego wiersza z tytulami i wylosowanie kota
		}

			std::string imie_string, rasa_string, agresywnosc, dodatkowa_cecha, uczulanie;

			std::getline(plik, imie_string, ';');
			std::getline(plik, agresywnosc, ';');
			std::getline(plik, rasa_string, ';');
			std::getline(plik, dodatkowa_cecha, '\n');

			int agresja = 0;
			char temp[2];
			if (agresywnosc != "10")
			{
				strcpy_s(temp, agresywnosc.c_str());
				agresja = temp[0] - 48;
			}
			else
			{
				agresja = 10;
			}

			strcpy_s(temp, dodatkowa_cecha.c_str());
			int dodatkowa_cecha_int = temp[0] - 48;

			plik.close();
			Kot nowy_kot(imie_string, agresja, rasa_string, dodatkowa_cecha_int);
			return nowy_kot;
	}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
		system("pause"); 
		throw 1;
	}
}

void stworzenie_klienta(Schronisko *_schronisko)
{
	int		odp;
	int		jakie_zwierze;
	bool	uczulenie = true;
	int		ile_zwierzat, uczulenie_int;

	system("cls");
	std::cout << "No to zaczynamy!\nCzy klient chce starac sie o adopcje czy oddac zwierze?\n1. Adopcja :)\n2. Oddanie :(\n\n Twoja odpowiedz: ";
	odpowiedz_zakres(odp, 1, 2);

	switch (odp)
	{
	case 1:

		system("cls");
		std::cout << "Formularz wstepny:\nIlosc zwierzat w domu: ";
		wczytywanie_cyfr_z_konsoli(ile_zwierzat);
		std::cout << "Uczulenie na siersc (1 - tak, 2 - nie):  ";

		odpowiedz_zakres(uczulenie_int, 1, 2);
		if (uczulenie_int == 2) uczulenie = false;
		else uczulenie = true;

		std::cout << "Czego szuka klient (1 - psa, 2 - kota):  ";
		odpowiedz_zakres(jakie_zwierze, 1, 2);
		if (jakie_zwierze == 1)
		{
			Pies potencjalny; //pies ktory bedzie zabrany do domu - nie moze nalezec do schroniska
			Klient<Pies> _klient1(ile_zwierzat, uczulenie);
			_schronisko->rozstrzygnij_prosbe(_klient1, potencjalny);
		}
		if (jakie_zwierze == 2)
		{
			Kot potencjalny;
			Klient<Kot> _klient2(ile_zwierzat, uczulenie);
			_schronisko->rozstrzygnij_prosbe(_klient2, potencjalny);
		}
		break;
	case 2:
		system("cls");
		std::cout << "Jakie zwierze przyniosl klient? (1 - psa, 2 - kota): ";
		do
		{
			odpowiedz_zakres(jakie_zwierze, 1, 2);
		} while (jakie_zwierze != 1 && jakie_zwierze != 2);
		if (jakie_zwierze == 1)
		{
			Pies pies_klienta = wczytaj_z_pliku_psa(*_schronisko);
			Klient<Pies> klient(pies_klienta);
			_schronisko->wez_zwierze(klient.oddaj_zwierze());
		}
		if (jakie_zwierze == 2)
		{
			try
			{
				Kot kot_klienta = wczytaj_z_pliku_kota(*_schronisko);
				Klient<Kot> klient(kot_klienta);
				_schronisko->wez_zwierze(klient.oddaj_zwierze());
			}
			catch (int kod)
			{
				//f (kod == 1);
			}
		}
		break;
	}
}
