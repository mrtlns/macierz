//
//  menu_klas.h
//  projektZPO
//
//  Created by martin and alina
//

#ifndef menu_klas_h
#define menu_klas_h

#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>

#include "macierz_klas.h" // Dołączenie pliku nagłówkowego z deklaracją klasy Macierz

// #include <bits/stdc.h>

using namespace std;

// Klasa Menu służy do zarządzania operacjami na macierzach
class Menu {
public:
    void start() {  // Uruchamia pętlę menu, obsługując operacje użytkownika do momentu wyjścia ('q')
        char choice;
        do {
            printMenu();                // Wyświetla menu operacji
            choice = getUserChoice();   // Pobiera wybór użytkownika
            processChoice(choice);      // Przetwarza wybór użytkownika
        } while (choice != 'q');        // Wyjście z pętli po wyborze 'q' (wyjście)
    }
    
private:
    Macierz m1;     // Obiekt klasy Macierz dla pierwszej macierzy
    Macierz m2;     // Obiekt klasy Macierz dla drugiej macierzy
    
    void printMenu() const {        // Funkcja wypisywania interfejsu
        cout << "\n========== Menu ==========\n";
        cout << "a) Wpisz 1 Macierz\n";
        cout << "b) Wpisz 2 Macierz\n";
        cout << "c) Pokaz 1 i 2 Macierz\n";
        cout << "d) Suma Macierzy\n";
        cout << "e) Wynik Mnożenie\n";
        cout << "f) Transponowanie 1 Macierz\n";
        cout << "g) Transponowanie 2 Macierz\n";
        cout << "h) Wyznacznik 1 Macierzy\n";
        cout << "i) Wyznacznik 2 Macierzy\n";
        cout << "j) Odwrotna 1 Macierz\n";
        cout << "k) Odwrotna 2 Macierz\n";
        cout << "q) Quit\n";
        cout << "==========================\n";
    }
    
    char getUserChoice() const {    // Pobieranie wybora użytkownika
        cout << "Podaj numer operacji: ";
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Czyszczenie bufora wejściowego
        return tolower(choice);     // Konwersja wyboru do małych liter
    }
    
    void processChoice(char choice) {   // Przetwarzanie wybora użytkownika i wykonanie odpowiedniej operacji
        try {
            switch (choice) {
                case 'a':
                    cout << "Podaj wartość macierzy 1:\n";
                    cin >> m1;
                    break;
                case 'b':
                    cout << "Podaj wartość macierzy 2:\n";
                    cin >> m2;
                    break;
                case 'c':
                    cout << "Macierz 1:\n" << m1;
                    cout << "\nMacierz 2:\n" << m2;
                    break;
                case 'd':
                    cout << "Suma Macierzy:\n" << (m1 + m2);
                    break;
                case 'e':
                    cout << "Wynik Mnozenia:\n" << (m1 * m2);
                    break;
                case 'f':
                    cout << "Transponuj 1 Macierz:\n" << m1.Transponuj();
                    break;
                case 'g':
                    cout << "Transponuj 2 Macierz:\n" << m2.Transponuj();
                    break;
                case 'h':
                    cout << "Wyznacznik 1 Macierzy: " << m1.Wyznacznik() << "\n";
                    break;
                case 'i':
                    cout << "Wyznacznik 2 Macierzy: " << m2.Wyznacznik() << "\n";
                    break;
                case 'j':
                    cout << "Odwrotna 1 Macierz 1:\n" << m1.Odwrotna();
                    break;
                case 'k':
                    cout << "Odwrotna 2 Macierz:\n" << m2.Odwrotna();
                    break;
                case 'q':
                    cout << "Do widzenia.\n";
                    break;
                default:
                    cout << "Niepoprawna odpowiedź.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";      // Wyświetlanie błędu, jeśli coś poszło nie tak
        }
    }
};

#endif /* menu_klas_h */
