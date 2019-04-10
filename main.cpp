#include "funkcje.h"
#include "resource.h"

using namespace std;

int main()
{
//  Jêzyk Polski w konsoli
    setlocale(LC_ALL, "");
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);

//  Pseudolosowoœæ z czasem
    srand(time(NULL));

    unsigned int wylosowane[LOSUJ_MAX]; // Tablica z adresami s³ów
    unsigned int iWylosowanych = 0; // Aktualnie wylosowanych adresów

    cout << "-==|Program do sprawdzania szybkoœci pisania na klawiaturze|==-\n"
         << "-==| KeyShark |==-\n\n";

//  Zliczenie liczby s³ów w s³owniku i obs³uga b³êdu
    char path[] = SLOWNIK;
    int lWierszy = IleWierszy(path); // Liczba wierszy/s³ów w s³owniku
        if(lWierszy == -1){cout << "Error!\nNie odnaleziono s³ownika.\nBrak pliku \""; color(BLUE, path); cout << "\"\n"; getch(); return 0;}
        if(lWierszy == -2){cout << "Error!\nNieznany wyj¹tek."; getch(); return 0;}
    string *slowa = new string[lWierszy];
    PrzepiszSlowa(path, slowa);

//  Pobieranie liczby s³ów do wylosowania
    cout << "Liczba s³ów w s³owniku: "; color(RED, lWierszy);
    cout << "\nPodaj liczbê s³ów któr¹ mam dla Ciebie wylosowaæ: ";
    bool a;
    do{
        color(RED);
        a = false;
        cin.clear();
        cin.sync();
        cin >> iWylosuj;
        color(STANDARD);
        if (iWylosuj > LOSUJ_MAX){ a = true; cout << "Porywasz siê z motyk¹ na s³oñce.\nWybierz liczbê do "; color(RED, LOSUJ_MAX); cout << ": "; }
    }while(cin.fail() || a == true);

    if (iWylosuj>0){
    //  Losowanie numerów linijek w s³owniku do tablicy wylosowane[]
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
    //  Przepisywanie s³ów z wylosowanych wierszy do nowej tablicy
        //cout << "Wylosowane s³owa: \n";
        string SlowaWylosowane[iWylosowanych];
        for(unsigned int i=0; i<iWylosowanych;i++){
            SlowaWylosowane[i] = slowa[wylosowane[i]];
    #ifdef _DEBUG
            cout << "\t" << SlowaWylosowane[i] << endl; // Wypisanie s³ów
    #endif
        }

    #ifdef _DEBUG
        getch();
    #endif

        delete[] slowa; // Usuwanie tablicy ze slowami

        system("cls");
        cout << "Zaraz zacznie siê zabawa.\n Wciœnij "; color(YELLOW, "SPACE"); cout << " aby zacz¹æ\n";

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
            cout << "Wylosowane s³owo: "; color(YELLOW, SlowaWylosowane[i]); cout << endl;
            gotoxy(poz_x, poz_y);
            poz_y += 7;
            float start = GetTickCount();
            getline(cin, Wpisywane[i]);
            float stop = GetTickCount();
            double roznica = ((stop - start)/1000);
            int bledy = LiczbaBledow(SlowaWylosowane[i], Wpisywane[i]);
            cout << "\nCzas pisania s³owa: \t"; color(GREEN, roznica); cout << " sekundy\n";
            if(bledy > 0){
                cout << "Liczba b³êdów w s³owie: "; color(GREEN, bledy); cout << endl;
                Beep(600, 400); // DŸwiêk
            };
            cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=";
            cout << endl << endl;
            CzasTotal += roznica;
            BledyTotal += bledy;
        };
        cout << "Ca³kowiy czas: \t\t"; color(BLUE, CzasTotal); cout << " sekundy\n"
             << "Œredni czas: \t\t"; color(BLUE, CzasTotal/iWylosowanych); cout << " sekundy\n"
             << "Liczba b³êdów: \t\t"; color(RED, BledyTotal);
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

    cout << "\n\nWciœnij dowolny klawisz, aby kontynuowaæ...";

    getch();
    return 0;
}
