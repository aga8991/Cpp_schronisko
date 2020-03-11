#include "Schronisko.h"

//numery zwierzat w schronisku musza byc aktualizowane aby poprawne byly obliczenia nr zwierzaka ktory idzie do adopcji
void aktualizowanie_nr(std::vector<class Pies> &_pieski)
{
	for (int i = 0; i < _pieski.size(); i++)
	{
		_pieski.at(i).nadaj_nr(i + 1);
	}
}

void aktualizowanie_nr(std::vector<class Kot> &_kotki)
{
	for (int i = 0; i < _kotki.size(); i++)
	{
		_kotki.at(i).nadaj_nr(i + 1);
	}
}

void wczytywanie_cyfr_z_konsoli(int& _odp)
{
	std::cin >> _odp;
	if (std::cin.fail()) 
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
}

//wczytywanie z konsoli tylko liczb z zadanego zakresu
void odpowiedz_zakres(int &_odp, int _poczatek, int _koniec)
{
	do {
		wczytywanie_cyfr_z_konsoli(_odp);
	} while (_odp <_poczatek  || _odp > _koniec);
}

//wczytywanie z konsoli stringow
void odpowiedz_string(std::string& _odp)
{
	while (1)
	{
		std::cin >> _odp;
		if (std::cin.fail()) 
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else break;
	}
}

Schronisko::Schronisko()
{
	std::cout << "Twoje schronisko na razie jest puste :(\nDodaj zwierzeta i zacznij przyjmowac klientow!\n";
	system("pause");
	dodaj_zwierzaka();
}

//dodawanie zwierzat z pliku lub reczne tworzenie
//nazwa pliku do wpisania: BazaZwierzat
void Schronisko::dodaj_zwierzaka()
{
	int	odp = 0;
	system("cls");
	std::cout << "Powiedz mi jak chcesz to zrobiæ.\n1.Dodaj zwierzaki z pliku.\n2.Stworz wlasnego zwierzaka." << std::endl;
	odpowiedz_zakres(odp,1,2);

	switch (odp)
	{
	case 1:
		dodaj_zwierzaki_z_pliku();
		break;
	case 2:
		stworz_zwierze();
		break;
	}
}

void Schronisko::stworz_zwierze()
{
	int				odp, odp2;
	std::string		nowe_imie, nowa_rasa;
	int				agresja, dodatkowa_cecha;
	bool			uczulanie = 0;

	std::cout << "Jakie zwierze chcialbys stworzyc?\n1.Psa\n2.Kota\nOdpowiedz: ";
	odpowiedz_zakres(odp,1,2);

	//case 1 i 2 wykorzystane do stworzenia psa, case 2 do stworzenia kota
	switch (odp)
	{
	case 1:
		if (pieski.size() == 25)
		{
			std::cout << "Brak miejsca dla nowego psa. Sprobuj ponownie pozniej. " << std::endl;
			break;
		}
		else
		{
			system("cls");
			std::cout << "Swietnie! Na poczatek wypelnij, krotki formularz..." << std::endl << "Czy siersc psa bedzie uczulac? (1 - tak, 2 - nie) Twoja odp: ";
			odpowiedz_zakres(odp2,1,2);
			if (odp2 == 1) uczulanie = true;
			else uczulanie = false;
		}
	case 2:
		if (odp == 2 && kotki.size() == 15)
		{
			std::cout << "Brak miejsca dla nowego kota. Sprobuj ponownie pozniej." << std::endl;
			break;
		}
		else
		{
			std::cout << "Imie zwierzaka: ";
			odpowiedz_string(nowe_imie);

			std::cout << "Rasa:";
			odpowiedz_string(nowa_rasa);

			std::cout << "Poziom agresji w skali od 0 do 10: ";
			odpowiedz_zakres(agresja, 0, 10);

			if (odp == 1)
			{
				std::cout << "Wielkosc psa (1 - maly, 2 - sredni, 3 - duzy): ";
				odpowiedz_zakres(dodatkowa_cecha, 1, 3);

				try
				{
					if (pieski.size() == 0) throw 1;
					Pies nowy_pies(nowe_imie, agresja, nowa_rasa, dodatkowa_cecha, uczulanie, pieski.back().jaki_numer() + 1);
					pieski.push_back(nowy_pies);
				} catch (...) 
				{
					Pies nowy_pies(nowe_imie, agresja, nowa_rasa, dodatkowa_cecha, uczulanie, 1);
					pieski.push_back(nowy_pies);
				}
				system("pause");
			}
			else
			{
				std::cout << "Srodowisko kota (1 - dom, 2 - obojetnie, 3 - potworko): ";
				odpowiedz_zakres(dodatkowa_cecha, 1, 3);

				try
				{
					if (kotki.size() == 0) throw 1;
					Kot nowy_kot(nowe_imie, agresja, nowa_rasa, dodatkowa_cecha, kotki.back().jaki_numer() + 1);
					kotki.push_back(nowy_kot);
				}
				catch (...)
				{
					Kot nowy_kot(nowe_imie, agresja, nowa_rasa, dodatkowa_cecha, 1);
					kotki.push_back(nowy_kot);
				}
				system("pause");
			}
		}
		break;
	}
}

void Schronisko::dodaj_zwierzaki_z_pliku()
{
	std::ifstream	plik;
	std::string		nazwa_pliku;

	std::cout << "\nNazwa pliku: ";
	std::cin >> nazwa_pliku;		//BazaZwierzat
	nazwa_pliku += ".csv";

	plik.open(nazwa_pliku.c_str(), std::ifstream::in);
	if (!plik.fail())
	{
		std::string	wczytywany_wiersz;
		std::getline(plik, wczytywany_wiersz);    //wczytanie pierwszego wiersza z tytulami

		while (plik.good()) 		//wczytanie zwierzakow
		{
			std::string rodzaj, imie_string, rasa_string, agresywnosc, dodatkowa_cecha, uczulanie;

			std::getline(plik, rodzaj, ';');
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

			if (rodzaj == "Pies")
			{
				try {
					if (pieski.size() == 25) throw 1;
					if (pieski.size() == 0) throw 2;
					Pies nowy_pies(imie_string, agresja, rasa_string, dodatkowa_cecha_int, uczulony, pieski.back().jaki_numer() + 1);
					pieski.push_back(nowy_pies);
				} // wykorzystano try catch aby nie przepelnic schroniska i gdy wektor pusty
				catch (int kod) 
				{
					if (kod == 1)
					{
						std::cout << "Brak miejsca dla nowego psa. Sprobuj ponownie pozniej. " << std::endl; 
						system("pause");
					}
					if (kod == 2)
					{
						Pies nowy_pies(imie_string, agresja, rasa_string, dodatkowa_cecha_int, uczulony, 1);
						pieski.push_back(nowy_pies);
					}
				}
			}
			if (rodzaj == "Kot")
			{
				try {
					if (kotki.size() == 15) throw 1;
					if (kotki.size() == 0) throw 2;
					Kot nowy_kot(imie_string, agresja, rasa_string, dodatkowa_cecha_int, kotki.back().jaki_numer() + 1);
					kotki.push_back(nowy_kot);
				}
				catch (int kod) 
				{ 
					if (kod == 1)
					{
						std::cout << "Brak miejsca dla nowego kota. Sprobuj ponownie pozniej." << std::endl; 
						system("pause");
					}
					if (kod == 2)
					{
						Kot nowy_kot(imie_string, agresja, rasa_string, dodatkowa_cecha_int, 1);
						kotki.push_back(nowy_kot);
					}
				}
			}
		}
		plik.close();
		}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
		system("pause");
	}
}

void Schronisko::wyswietl_zwierzaki()
{
	// wyswietlanie psow
	system("cls");
	std::cout << "Psy: " << std::endl;
	if (pieski.empty() == true) std::cout << "Brak pieskow." << std::endl;
	else
	{
		for (int i = 0; i < pieski.size(); i++)
		{
			int ile_tab;
			std::cout << "Imie: " << pieski.at(i).jakie_imie();
			if (pieski.at(i).jakie_imie().size() < 9) std::cout << "\t";
			if (pieski.at(i).jakie_imie().size() < 4)std::cout << "\t";
			else std::cout << "\t";
			std::cout << "Rasa: " << pieski.at(i).jaka_rasa();
			if (pieski.at(i).jaka_rasa().size() < 12) std::cout << "\t";
			if (pieski.at(i).jaka_rasa().size() < 10) std::cout << "\t";
			if (pieski.at(i).jaka_rasa().size() < 4)std::cout << "\t";
			std::cout << "Poziom agresji: " << pieski.at(i).jaka_agresja() << "\tWielkosc: ";
			if (pieski.at(i).jak_duzy() == 1) std::cout << "maly\t";
			if (pieski.at(i).jak_duzy() == 2) std::cout << "sredni";
			if (pieski.at(i).jak_duzy() == 3) std::cout << "duzy\t";
			if (pieski.at(i).czy_uczula() == true) std::cout << "\tUczula" << std::endl;
			if (pieski.at(i).czy_uczula() == false) std::cout << "\tNie uczula" << std::endl;
		}
	}

	//wyswietlanie kotow
	std::cout << "\nKoty: " << std::endl;
	if (kotki.empty() == true) std::cout << "Brak kotkow." << std::endl;
	else
	{
		for (int i = 0; i < kotki.size(); i++)
		{
			std::cout << "Imie: " << kotki.at(i).jakie_imie();
			if (kotki.at(i).jakie_imie().size() < 9) std::cout << "\t";
			if (kotki.at(i).jakie_imie().size() < 4)std::cout << "\t";
			else std::cout << "\t";
			std::cout << "Rasa: " << kotki.at(i).jaka_rasa();
			if (kotki.at(i).jaka_rasa().size() < 12) std::cout << "\t";
			if (kotki.at(i).jaka_rasa().size() < 10) std::cout << "\t";
			if (kotki.at(i).jaka_rasa().size() < 4)std::cout << "\t";
			std::cout << "Poziom agresji: " << kotki.at(i).jaka_agresja() << "\tTyp kota: ";
			if (kotki.at(i)._czy_kot_jest_domowy() == 1) std::cout << "domowy" << std::endl;
			if (kotki.at(i)._czy_kot_jest_domowy() == 2) std::cout << "jest mu obojetnie" << std::endl;
			if (kotki.at(i)._czy_kot_jest_domowy() == 3) std::cout << "podworkowy" << std::endl;
		}
	}
	system("pause");
}

// sprawdzenie mozliwosci adopcji kota
bool Schronisko::zgodnosc_cech(Kot _kot, Klient<Kot> obecny_klient)
{
	if (obecny_klient.czy_ma_uczulenie() == false)
	{
		if ((obecny_klient.jakiej_rasy_szuka() == _kot.jaka_rasa()) || (obecny_klient.jakiej_rasy_szuka() == "obojetnie"))
		{
			if ((obecny_klient.czy_sa_inne_zwierzeta() == false) || (obecny_klient.czy_sa_inne_zwierzeta() == true && _kot.jaka_agresja() < 5))
			{
				return true;
			}
		}
	}
	return false;
}

// sprawdzenie mozliwosci adopcji psa
bool Schronisko::zgodnosc_cech(Pies _pies, Klient<Pies> obecny_klient)
{
	if ((obecny_klient.jakiej_rasy_szuka() == _pies.jaka_rasa()) || (obecny_klient.jakiej_rasy_szuka() == "obojetnie"))
	{
		if (!(obecny_klient.czy_ma_uczulenie() == _pies.czy_uczula()) || (obecny_klient.czy_ma_uczulenie() == false))
		{
			if ((obecny_klient.czy_sa_inne_zwierzeta() == false) || (obecny_klient.czy_sa_inne_zwierzeta() == true && _pies.jaka_agresja() < 5))
			{
				return true;
			}
		}
	}
	return false;
}

// rozstrzyga mozliwosc adopcji i w przypadku zgody oddaje psa
void Schronisko::rozstrzygnij_prosbe(Klient<Pies>& obecny_klient, Pies &_potencjalny)
{
	std::vector<Pies> psy_do_wyboru;
	for (int i = 0; i < pieski.size(); i++)
	{
		if (zgodnosc_cech(pieski[i], obecny_klient) == true)
		{
			psy_do_wyboru.push_back(pieski[i]);
		} // jesli cechy sa zgodne to tworzony jest pomocniczy wektor dostepnych zwierzat
	}

	if (psy_do_wyboru.empty()== false)
	{
		std::cout << "Pieski ktore mozesz zaadoptowac:" << std::endl;
		for (int i = 0; i < psy_do_wyboru.size(); i++)
		{
			std::cout << i + 1 << ". " << psy_do_wyboru.at(i).jakie_imie() << " -> ";
			if (psy_do_wyboru.at(i).jak_duzy() == 1) std::cout << "maly pies" << std::endl;
			if (psy_do_wyboru.at(i).jak_duzy() == 2) std::cout << "sredni pies" << std::endl;
			if (psy_do_wyboru.at(i).jak_duzy() == 3) std::cout << "duzy pies" << std::endl;
		}
		std::cout << "Ktorego wybierasz? Twoj wybor: ";
		int odp;
		odpowiedz_zakres(odp, 1, psy_do_wyboru.size() + 1);

		odp = psy_do_wyboru.at(odp - 1).jaki_numer();	//zmiana numeru zwierzaka z wektora dostepnych do adopcji na nr w wektorze schroniska

		std::cout << "Chcesz najpierw wyprowadzic psa? (1 - tak, 2 - nie): ";
		int odp2;
		odpowiedz_zakres(odp2, 1, 2);
		if (odp2 == 1)
		{
			if ((pieski.at(odp - 1).mozliwy_atak()) == false)
			{
				_potencjalny = oddaj_psa(odp - 1);
				obecny_klient.wez_zwierze(&_potencjalny);
				std::cout << pieski.at(odp - 1).jakie_imie() << " znalazl(a) nowy dom!\n";
				system("pause");
				pieski.erase(pieski.begin() + odp - 1);
				aktualizowanie_nr(pieski);
			}	//jesli zwierze zaatakuje to klient go nie wezmie
		}
		else
		{
			_potencjalny = oddaj_psa(odp - 1);
			obecny_klient.wez_zwierze(&_potencjalny);
			std::cout << pieski.at(odp - 1).jakie_imie() << " znalazl(a) nowy dom!\n";
			system("pause");
			pieski.erase(pieski.begin() + odp - 1);
			aktualizowanie_nr(pieski);
		}
	}
	else
	{
		std::cout << "Niestety nie mamy odpowiedniego psa dla Ciebie." << std::endl;
		system("pause");
	}
}

void Schronisko::rozstrzygnij_prosbe(Klient<Kot>& obecny_klient, Kot &_potencjalny)
{
	std::vector<Kot> koty_do_wyboru;
	for (int i = 0; i < kotki.size(); i++)
	{
		if (zgodnosc_cech(kotki[i], obecny_klient) == true)
		{
			koty_do_wyboru.push_back(kotki[i]);
		}
	}	// tworzenie wektora z kotami ktorych cechy sa zgodne

	if (koty_do_wyboru.empty() == false)
	{
		std::cout << "Kotki ktore mozesz zaadoptowac:" << std::endl;
		for (int i = 0; i < koty_do_wyboru.size(); i++)
		{
			std::cout << i + 1 << ". " << koty_do_wyboru.at(i).jakie_imie() << " -> ";
			if (koty_do_wyboru.at(i)._czy_kot_jest_domowy() == 1) std::cout << "kot domowy" << std::endl;
			if (koty_do_wyboru.at(i)._czy_kot_jest_domowy() == 2) std::cout << "brak wymagan" << std::endl;
			if (koty_do_wyboru.at(i)._czy_kot_jest_domowy() == 3) std::cout << "kot podworkowy" << std::endl;
		}
		std::cout << "Ktorego wybierasz? Twoj wybor: ";
		int odp;
		odpowiedz_zakres(odp, 1, koty_do_wyboru.size() + 1);

		odp = koty_do_wyboru.at(odp - 1).jaki_numer();	//zmiana numeru zwierzaka z wektora dostepnych do adopcji na nr w wektorze schroniska

		std::cout << "Chcesz najpierw pobawic sie z kotem? (1 - tak, 2 - nie): ";
		int odp2;
		odpowiedz_zakres(odp2, 1, 2);
		if (odp2 == 1)
		{
			if ((kotki.at(odp - 1).mozliwy_atak()) == false)
			{
				_potencjalny = oddaj_kota(odp - 1);
				obecny_klient.wez_zwierze(&_potencjalny);
				std::cout << kotki.at(odp - 1).jakie_imie() << " znalazl(a) nowy dom!\n";
				system("pause");
				kotki.erase(kotki.begin() + odp - 1);
				aktualizowanie_nr(kotki);
			}
		}
		else
		{
			_potencjalny = oddaj_kota(odp - 1);
			obecny_klient.wez_zwierze(&_potencjalny);
			std::cout << kotki.at(odp - 1).jakie_imie() << " znalazl(a) nowy dom!\n";
			system("pause");
			kotki.erase(kotki.begin() + odp - 1);
			aktualizowanie_nr(kotki);
		}
	}
	else
	{
		std::cout << "Niestety nie mamy odpowiedniego kota dla Ciebie." << std::endl;
		system("pause");
	}
}

void Schronisko::wez_zwierze(Pies* _oddane)
{
	try 
	{
		if (pieski.size() == 25) throw 1;
		pieski.push_back(*_oddane);
		aktualizowanie_nr(pieski);
		std::cout << "Pies zostal oddany. " << pieski.back().jakie_imie() << " dolacza do schroniska!" << std::endl;
		system("pause");
	}
	catch (...) 
	{
		std::cout << "Schronisko przepelnione. Nie mozna oddac zwierzecia. \n"; 
		system("pause");
	}
}

void Schronisko::wez_zwierze(Kot *_oddane)
{
	try
	{
		if (kotki.size() == 15) throw 1;
		kotki.push_back(*_oddane);
		aktualizowanie_nr(kotki);
		std::cout << "Kot zostal oddany. " << kotki.back().jakie_imie() << " dolacza do schroniska!" << std::endl;
		system("pause");
	}
	catch (...)
	{
		std::cout << "Schronisko przepelnione. Nie mozna oddac zwierzecia. \n";
		system("pause");
	}
}