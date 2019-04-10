#ifndef __FUNKCJE2_H
#define __FUNKCJE2_H

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <windows.h>

#define LOSUJ_MAX 100
#define SLOWNIK "slownik.txt"

#define STANDARD 7
#define BIALY 15

#define CIEMNY -8

#define RED 12
#define GREEN 10
#define BLUE 9
#define CYJAN 11
#define MAGENTA 13
#define YELLOW 14
#define BLACK 112

using namespace std;


unsigned int iWylosuj = 0; // Liczba ile mamy wylosowaæ s³ów
double CzasTotal = 0.0; // Ca³kowity czas wpisywania s³ów
int BledyTotal = 0; // Ca³kowita liczba b³êdów

void Znak(){
    int z;
    do {
        z = getch();
        cout << "Kod: " << z << endl;
    }while(z != 17);
};

//  Losuje s³owo
inline int Wylosuj(int losuj_do){
    return (rand()*rand())%(losuj_do - 1) + 1;
};

//  Kolorowanie s³ów w konsoli
void color(int c) {
     HANDLE uchwyt;
     uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(uchwyt,c);
}
void color(int c, int tekst) {
     HANDLE uchwyt;
     uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(uchwyt,c);
     cout << tekst;
     SetConsoleTextAttribute(uchwyt,7);
}
void color(int c, double tekst) {
     HANDLE uchwyt;
     uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(uchwyt,c);
     cout << tekst;
     SetConsoleTextAttribute(uchwyt,7);
}
void color(int c, string tekst) {
     HANDLE uchwyt;
     uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(uchwyt,c);
     cout << tekst;
     SetConsoleTextAttribute(uchwyt,7);
}

void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//  Sprawdza czy liczba by³a wylosowana
bool czyBylaWylosowana (unsigned int iLiczba, unsigned int tab[], int ile){
    if(ile <= 0){
        return false;
    }
    int i = 0;
    do {
        if(tab[i] == iLiczba){
            return true;
        }
        i++;
    }while(i < ile);

    return false;
};

//  Liczy liczbê b³êdów we wpisywanym wyrazie
//  oraz dope³nienia krótszy wyraz
int LiczbaBledow(string wylosowane, string &wpisywane){
    if(wpisywane.length() < wylosowane.length()){
        for(unsigned int i = wpisywane.length(); i < wylosowane.length(); i++){
            wpisywane += " ";
        }
    } else if(wpisywane.length() > wylosowane.length()){
        for(int unsigned i = wylosowane.length(); i < wpisywane.length(); i++){
            wylosowane += " ";
        }
    }
    int bledy = 0;
    for(int unsigned i = 0; i < wpisywane.length(); i++){
        if(wylosowane[i] != wpisywane[i]){
            //cout << "\n\n" << wylosowane[i] << "\t\t" << wpisywane[i] << endl;
            bledy++;
        }
    }
    return bledy;
}

#endif
