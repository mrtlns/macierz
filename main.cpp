#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>

#include "menu_klas.h"      // Dołączenie pliku nagłówkowego z deklaracją klasy Menu
#include "macierz_klas.h"   // Dołączenie pliku nagłówkowego z deklaracją klasy Macierz

// #include <bits/stdc.h>

using namespace std;

// Funkcja main() - główna funkcja programu
int main() {
    Menu menu;          // Utworzenie obiektu klasy Menu
    menu.start();       // Wywołanie start() klasy Menu
    return 0;           // Zakończenie programu z kodem powrotu 0
}
