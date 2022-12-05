// projektZaliczenie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

int menu(int orderType) {
    cout << endl << "jestem tu tylko zeby nie wywalac bledu, zrob mnie w oddzielnym pliku ;)";
    return 0;
};

int main()
{
    
    string name, address;
    int orderType, tableNumber, hour;
    bool success = false;


    // Powitanie klienta i podanie danych karczmy
    cout << "Witaj w karczmie 'U Krasnoluda'" << endl;
    cout << "na ulicy Smoczej Skaly 24/7 w Mythrondale" << endl;
    cout << "jest to najlepsza karczma w okolicy prowadzona przez Brunhilde Bumby-Trotter" << endl;
    cout << "Jestesmy otwarci od godziny 12:00 do 23:00" << endl;


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
            // Tutaj zainicjowanie funkcji z menu z parametrem numer stolika i orderType(1 - na miejscu)
            menu(orderType);
            success = true;
        }
        else if (orderType == 2) {
            cout << "Podaj adres do zamowienia w formacie(ulica/numer ulicy)" << endl;
            getline(cin >> ws, address);
            cout << "Podaj o ktorej godzinie zamowienia ma zostac dostarczone (zamowienia dostarczane sa tylko o pelnych godzinach!)" << endl;
            cin >> hour;

            if (hour >= 12 && hour <= 23) {
                cout << endl << "Zamowienie na godzine: " << hour << " zostanie dostarczone na adres: " << address << " po wyborze z menu, zapraszamy";
                // Tutaj zainicjowanie funkcji z menu z parametrem orderType(2 - dostawa)
                menu(orderType);
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
}