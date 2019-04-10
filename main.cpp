#include "funkcje.h"
#include "resource.h"

using namespace std;

int main()
{
//  J�zyk Polski w konsoli
    setlocale(LC_ALL, "");
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);

//  Pseudolosowo�� z czasem
    srand(time(NULL));

    unsigned int wylosowane[LOSUJ_MAX]; // Tablica z adresami s��w
    unsigned int iWylosowanych = 0; // Aktualnie wylosowanych adres�w

    cout << "-==|Program do sprawdzania szybko�ci pisania na klawiaturze|==-\n"
         << "-==| KeyShark |==-\n\n";

//  Zliczenie liczby s��w w s�owniku i obs�uga b��du
    char path[] = SLOWNIK;
    int lWierszy = IleWierszy(path); // Liczba wierszy/s��w w s�owniku
        if(lWierszy == -1){cout << "Error!\nNie odnaleziono s�ownika.\nBrak pliku \""; color(BLUE, path); cout << "\"\n"; getch(); return 0;}
        if(lWierszy == -2){cout << "Error!\nNieznany wyj�tek."; getch(); return 0;}
    string *slowa = new string[lWierszy];
    PrzepiszSlowa(path, slowa);

//  Pobieranie liczby s��w do wylosowania
    cout << "Liczba s��w w s�owniku: "; color(RED, lWierszy);
    cout << "\nPodaj liczb� s��w kt�r� mam dla Ciebie wylosowa�: ";
    bool a;
    do{
        color(RED);
        a = false;
        cin.clear();
        cin.sync();
        cin >> iWylosuj;
        color(STANDARD);
        if (iWylosuj > LOSUJ_MAX){ a = true; cout << "Porywasz si� z motyk� na s�o�ce.\nWybierz liczb� do "; color(RED, LOSUJ_MAX); cout << ": "; }
    }while(cin.fail() || a == true);

    if (iWylosuj>0){
    //  Losowanie numer�w linijek w s�owniku do tablicy wylosowane[]
        while(iWylosowanych<iWylosuj){
            unsigned int liczba = Wylosuj(lWierszy);
            if(czyBylaWylosowana(liczba, wylosowane, iWylosowanych) == false){
                wylosowane[iWylosowanych] = liczba;
                iWylosowanych++;
            }
        }

    #ifdef _DEBUG
    //    Wypisanie wylosowanych liczb
        iWylosowanych = 0;
        while(iWylosowanych<iWylosuj){
            cout << wylosowane[iWylosowanych] << endl;
            iWylosowanych++;
        }

    #endif

        //cout << Wylosuj(); // Sprawdzanie funkcji Wylosuj();
    //  Przepisywanie s��w z wylosowanych wierszy do nowej tablicy
        //cout << "Wylosowane s�owa: \n";
        string SlowaWylosowane[iWylosowanych];
        for(unsigned int i=0; i<iWylosowanych;i++){
            SlowaWylosowane[i] = slowa[wylosowane[i]];
    #ifdef _DEBUG
            cout << "\t" << SlowaWylosowane[i] << endl; // Wypisanie s��w
    #endif
        }

    #ifdef _DEBUG
        getch();
    #endif

        delete[] slowa; // Usuwanie tablicy ze slowami

        system("cls");
        cout << "Zaraz zacznie si� zabawa.\n Wci�nij "; color(YELLOW, "SPACE"); cout << " aby zacz��\n";

        int poz_x=9;
        int poz_y=2;
        char z;
        do{
            z = getch();
        }while(z != 32);
        system("cls");
        string Wpisywane[iWylosowanych]; // Tablica z wyrazami wpisywanymi
        for(unsigned int i = 0; i < iWylosowanych; i++){
            cin.clear();
            cin.sync();
            cout << "Wylosowane s�owo: "; color(YELLOW, SlowaWylosowane[i]); cout << endl;
            gotoxy(poz_x, poz_y);
            poz_y += 7;
            float start = GetTickCount();
            getline(cin, Wpisywane[i]);
            float stop = GetTickCount();
            double roznica = ((stop - start)/1000);
            int bledy = LiczbaBledow(SlowaWylosowane[i], Wpisywane[i]);
            cout << "\nCzas pisania s�owa: \t"; color(GREEN, roznica); cout << " sekundy\n";
            if(bledy > 0){
                cout << "Liczba b��d�w w s�owie: "; color(GREEN, bledy); cout << endl;
                Beep(600, 400); // D�wi�k
            };
            cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=";
            cout << endl << endl;
            CzasTotal += roznica;
            BledyTotal += bledy;
        };
        cout << "Ca�kowiy czas: \t\t"; color(BLUE, CzasTotal); cout << " sekundy\n"
             << "�redni czas: \t\t"; color(BLUE, CzasTotal/iWylosowanych); cout << " sekundy\n"
             << "Liczba b��d�w: \t\t"; color(RED, BledyTotal);
    } else delete[] slowa; // Usuwanie tablicy ze slowami

    color(BLACK);
#ifdef _DEBUG
    cout << "\n\nDEBUG\n";
#endif // _DEBUG
#ifndef _DEBUG
    cout << "\n\nRELEASE\n";
#endif // _DEBUG
    cout << "Skompilowano: " << __DATE__ << " o " << __TIME__;
    color(STANDARD);

    cout << "\n\nWci�nij dowolny klawisz, aby kontynuowa�...";

    getch();
    return 0;
}
