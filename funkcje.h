#ifndef __FUNKCJE_H
#define __FUNKCJE_H

#include "funkcje2.h"

//  Liczy iloœæ s³ów w s³owniku i sprawdza obecnoœæ pliku
int IleWierszy(string path){
    fstream slownik;
    string tmp;
    int lWierszy = 0;
    slownik.open(path, ios::in);
    if(slownik.good()){
        while(!slownik.eof()){
            getline(slownik, tmp);
            lWierszy++;
        }
        slownik.close();
        return lWierszy;
    } else {
        return -1; // Nie odnaleziono s³ownika
    }
    return -2; // Nieznany b³¹d
};

//  Przepisuje s³owa z pliku do tablicy slowa[]
void PrzepiszSlowa(string path, string *slowa){
    fstream slownik;
    int i = 0;
    slownik.open(path, ios::in);
    if(slownik.good()){
        while(!slownik.eof()){
            getline(slownik, slowa[i]);
            i++;
        }
        slownik.close();
    } else {
        cout << "Error!\nNie odnaleziono s³ownika.\nBrak pliku \""; color(RED, path); cout << "\"\n"; getch(); // Nie odnaleziono s³ownika
    }
};


#endif
