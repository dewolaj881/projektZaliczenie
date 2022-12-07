#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
using namespace std;

vector<string> nazwy;
vector<string> sklad;
vector<int> ceny;
int cena_za_calosc = 0;
vector<int> ilosci;
int porcje;

struct Zamowienie {
	string nazwaDania;
	int liczbaTegoDania = 0;
};
Zamowienie zamowioneDania[100];


void wczytajMenu()
{
	fstream plik;
	plik.open("Test.txt", ios::in);
	if (plik.good() == false)
	{
		cout << "Blad z plikiem.";
		exit(1);
	}

	string linia;
	int licznik = 0;
	while (getline(plik, linia))
	{
		switch (licznik)
		{
		case 0:
			nazwy.push_back(linia);
			break;
		case 1:
			sklad.push_back(linia);
			break;
		case 2:
			stringstream ss;
			ss << linia;
			int tymczasowa;
			ss >> tymczasowa;
			ceny.push_back(tymczasowa);
			break;
		}
		licznik++;
		if (licznik >= 3) licznik = 0;
	}
	plik.close();

	for (int i = 0; i < nazwy.size(); i++) ilosci.push_back(0);
	if (nazwy.size() != sklad.size() || sklad.size() != ceny.size()) exit(1);
}

bool pokazMenu()
{
	cout << "\x1B[2J\x1B[H";
	cout << "Menu (" << cena_za_calosc << " zl)" << endl;
	cout << "[0] - zakoncz dzialanie aplikacji" << endl;
	cout << "[1] - zakoncz dodawanie" << endl;
	int iloscPozycji = nazwy.size();
	iloscPozycji += 2;
	for (int i = 2; i < iloscPozycji; i++)
	{
		cout << "[" << i << "] - " << nazwy[i - 2] << " (" << sklad[i - 2] << ") - " << ceny[i - 2] << " szt. zlota" << endl;
	}
	cout << "Wybierz pozycje do dodania do podsumowania: ";

	int wybranaPozycja = 0;
	cin >> wybranaPozycja;

	if (wybranaPozycja == 0)
	{
		exit(0);
	}
	else if (wybranaPozycja == 1)
	{
		cout << "\x1B[2J\x1B[H";
		cout << "Czy napewno chcesz zakonczyc dodawnie pozycji do menu?" << endl;
		cout << "Potwierdz ponizsze zamowienie wybierajac tak: " << endl;
		cout << "------------------------------------------------" << endl;
		for (int i = 0; i < 10; i++) {
			if (zamowioneDania[i].liczbaTegoDania == 0) {

			}
			else {
				cout << zamowioneDania[i].liczbaTegoDania << "x " << zamowioneDania[i].nazwaDania << endl;
			}
		}
		cout << "------------------------------------------------" << endl;
		cout << cena_za_calosc << endl;
		cout << "------------------------------------------------" << endl;
		cout << "[1] - tak" << endl;
		cout << "[2] - nie" << endl;
		cout << "Wybor: ";
		int wybor = 0;
		cin >> wybor;
		if (wybor == 1) return false;
	}
	else if (wybranaPozycja >= 1)
	{
		cout << "Podaj liczbe porcji";
		cin >> porcje;
		zamowioneDania[wybranaPozycja - 1].liczbaTegoDania += porcje;
		//create list of dishes and their number
		zamowioneDania[wybranaPozycja - 1].nazwaDania = nazwy[wybranaPozycja - 1];
		zamowioneDania[wybranaPozycja - 1].liczbaTegoDania++;
		ilosci[wybranaPozycja - 2] += porcje;
	}

	cena_za_calosc = 0;
	for (int i = 0; i < ilosci.size(); i++)
	{
		cena_za_calosc += ilosci[i] * ceny[i];
	}

	return true;
}

int main()
{
	string name, address;
	int orderType, tableNumber, hour;
	bool success = false;
	// Powitanie klienta i podanie danych karczmy
	cout << "Witaj w karczmie 'U Krasnoluda' na ulicy Smoczej Skaly 24/7 w Mythrondale" << endl;
	cout << "Jest to najlepsza karczma w okolicy prowadzona przez Brunhilde Bumby-Trotter!" << endl;
	cout << "Jestesmy otwarci od godziny 12:00 do 23:00" << endl;
	cout << "Zamowienia na dostawe, dostarczane sa co godzine od 13:00 do 23:00" << endl;


	// Powitanie klienta i zebranie informacji o zamowieniu
	cout << "Jak sie nazywasz podrozniku?" << endl;
	cin >> name;

	do {
		cout << "Chcesz zamowic na miejscu czy na dowoz?" << endl;
		cout << "1 - na miejscu" << endl;
		cout << "2 - na dowoz" << endl;
		cin >> orderType;

		if (orderType == 1) {
			cout << "Podaj prosze numer stolika" << endl;
			cin >> tableNumber;
			cout << "Twoj stolik to " << tableNumber << endl;
			success = true;
		}
		else if (orderType == 2) {
			cout << "Podaj adres do zamowienia w formacie(ulica/numer ulicy)" << endl;
			getline(cin >> ws, address);
			cout << "Podaj o ktorej godzinie zamowienia ma zostac dostarczone (zamowienia dostarczane sa tylko o pelnych godzinach!)" << endl;
			cin >> hour;

			if (hour >= 12 && hour <= 23) {
				cout << endl << "Zamowienie na godzine: " << hour << " zostanie dostarczone na adres: " << address << " po wyborze z menu, zapraszamy";
				success = true;
			}
			else {
				cout << "Wybierz godzine w czasie dzialania restauracji pomiedzy 12 a 23" << endl;
				success = false;
			}
		}
		else {
			cout << "Podaj prawidlowy typ zamowienia!" << endl;
			success = false;
		}
	} while (success == false);

	wczytajMenu();
	bool menuTrwa = true;
	while (menuTrwa) menuTrwa = pokazMenu();
	return 0;
}