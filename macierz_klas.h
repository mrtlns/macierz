//
//  macierz_klas.h
//  projektZPO
//
//  Created by martin
//

#ifndef macierz_klas_h
#define macierz_klas_h

#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>
// #include <bits/stdc.h>

using namespace std;

class Macierz {
private:
    int wiersze;
    int kolumny;
    double **macierz;
    
public:
    Macierz();
    Macierz(int w, int k);
    Macierz(double **m, int w, int k);
    Macierz(const Macierz &);
    ~Macierz();
    
    double Wyznacznik();
    Macierz Transponuj();
    Macierz Odwrotna();
    
    Macierz operator+(const Macierz &) const;
    Macierz operator-(const Macierz &) const;
    Macierz operator*(const Macierz &) const;
    // Macierz &operator+=(const Macierz &);
    // Macierz &operator-=(const Macierz &);
    
    friend ostream &operator<<(ostream &, const Macierz &);
    friend istream &operator>>(istream &, Macierz &);
    
    int Wiersze() const { return wiersze; }
    int Kolumny() const { return kolumny; }
};

Macierz::Macierz() {
    wiersze = kolumny = 0;
    macierz = nullptr;
}

Macierz::Macierz(int w, int k) : wiersze(w), kolumny(k) {
    macierz = new double *[wiersze];
    for (int i = 0; i < wiersze; ++i) {
        macierz[i] = new double[kolumny];
        for (int j = 0; j < kolumny; ++j) {
            macierz[i][j] = 0.0;
        }
    }
}

Macierz::Macierz(double **m, int w, int k) {
    wiersze = w;
    kolumny = k;
    macierz = new double *[w];
    for (int i = 0; i < w; ++i) {
        macierz[i] = new double[k];
        for (int j = 0; j < k; ++j) {
            macierz[i][j] = m[i][j];
        }
    }
}

Macierz::Macierz(const Macierz &tmp) {
    wiersze = tmp.wiersze;
    kolumny = tmp.kolumny;
    macierz = new double *[tmp.wiersze];
    for (int i = 0; i < tmp.wiersze; i++) {
        macierz[i] = new double[tmp.kolumny];
        for (int j = 0; j < tmp.kolumny; j++) {
            macierz[i][j] = tmp.macierz[i][j];
        }
    }
}

Macierz::~Macierz() {
    if (macierz != nullptr) {
        for (int i = 0; i < wiersze; i++) {
            delete[] macierz[i];
        }
        delete[] macierz;
    }
}

double Macierz::Wyznacznik() {
    if (wiersze != kolumny) {
        cerr << "Nie można obliczyć wyznacznika dla macierzy o różnej liczbie wierszy i kolumn." << endl;
        return 0.0;
    }
    
    double det = 1.0;
    Macierz temp(*this);
    
    for (int i = 0; i < wiersze - 1; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < wiersze; ++k) {
            if (abs(temp.macierz[k][i]) > abs(temp.macierz[maxRow][i])) {
                maxRow = k;
            }
        }
        
        if (maxRow != i) {
            swap(temp.macierz[i], temp.macierz[maxRow]);
            det *= -1.0;
        }
        
        if (temp.macierz[i][i] == 0.0) {
            return 0.0;
        }
        
        for (int k = i + 1; k < wiersze; ++k) {
            double coeff = temp.macierz[k][i] / temp.macierz[i][i];
            for (int j = i; j < kolumny; ++j) {
                temp.macierz[k][j] -= coeff * temp.macierz[i][j];
            }
        }
    }
    
    for (int i = 0; i < wiersze; ++i) {
        det *= temp.macierz[i][i];
    }
    
    return det;
}

Macierz Macierz::Transponuj() {
    Macierz t(kolumny, wiersze);
    
    for (int i = 0; i < wiersze; ++i) {
        for (int j = 0; j < kolumny; ++j) {
            t.macierz[j][i] = macierz[i][j];
        }
    }
    
    return t;
}

Macierz Macierz::Odwrotna() {
    if (wiersze != kolumny || Wyznacznik() == 0) {
        cerr << "Macierz nie jest kwadratowa lub nie ma odwrotności." << endl;
        return Macierz();
    }
    
    Macierz jednostkowa(wiersze, kolumny);
    Macierz temp(*this);
    
    for (int i = 0; i < wiersze; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < wiersze; ++k) {
            if (fabs(temp.macierz[k][i]) > fabs(temp.macierz[maxRow][i])) {
                maxRow = k;
            }
        }
        
        if (maxRow != i) {
            swap(temp.macierz[i], temp.macierz[maxRow]);
            swap(jednostkowa.macierz[i], jednostkowa.macierz[maxRow]);
        }
        
        double pivot = temp.macierz[i][i];
        
        for (int j = 0; j < kolumny; ++j) {
            temp.macierz[i][j] /= pivot;
            jednostkowa.macierz[i][j] /= pivot;
        }
        
        for (int k = 0; k < wiersze; ++k) {
            if (k != i) {
                double factor = temp.macierz[k][i];
                for (int j = 0; j < kolumny; ++j) {
                    temp.macierz[k][j] -= factor * temp.macierz[i][j];
                    jednostkowa.macierz[k][j] -= factor * jednostkowa.macierz[i][j];
                }
            }
        }
    }
    
    return jednostkowa;
}

Macierz Macierz::operator+(const Macierz &tmp) const {
    if (wiersze != tmp.wiersze || kolumny != tmp.kolumny) {
        cout << "Nie można dodawać macierzy o różnych wymiarach!" << endl;
        Macierz blad;
        return blad;
    }
    
    int i, j;
    Macierz wynik = *this;
    
    for (i = 0; i < wynik.wiersze; i++) {
        for (j = 0; j < wynik.kolumny; j++) {
            wynik.macierz[i][j] += tmp.macierz[i][j];
        }
    }
    
    return wynik;
}

Macierz Macierz::operator*(const Macierz &tmp) const {
    if (tmp.wiersze != kolumny) {
        cout << "Nie można pomnożyć macierzy o takich wymiarach!" << endl;
        Macierz blad;
        return blad;
    }
    
    double **tab;
    int i, j, l;
    
    tab = new double *[wiersze];
    
    for (i = 0; i < wiersze; i++) {
        tab[i] = new double[tmp.kolumny];
    }
    
    for (i = 0; i < tmp.wiersze; i++) {
        for (j = 0; j < tmp.kolumny; j++) {
            for (l = 0, tab[i][j] = 0; l < tmp.wiersze; l++) {
                tab[i][j] += macierz[i][l] * tmp.macierz[l][j];
            }
        }
    }
    
    Macierz wynik(tab, wiersze, tmp.kolumny);
    
    for (i = 0; i < wiersze; i++) {
        delete[] tab[i];
    }
    
    delete[] tab;
    
    return wynik;
}

ostream &operator<<(ostream &os, const Macierz &tmp) {
    if (tmp.macierz == nullptr)
        return os;
    
    int i, j;
    
    for (i = 0; i < tmp.wiersze; i++) {
        for (j = 0; j < tmp.kolumny; j++) {
            cout << tmp.macierz[i][j] << "\t";
        }
        cout << endl;
    }
    
    return os;
}

istream &operator>>(istream &is, Macierz &tmp) {
    int w = 0, k = 0;
    int spr = 0;
    char znak = 0;
    
    double bufor[10];
    double *wsk[10];
    
    while (1) {
        while (1) {
            cin >> bufor[k];
            cin.get(znak);
            
            k++;
            
            if (znak == ';' || znak == '\n')
                break;
            
            if (k > 10) {
                cout << "Przekroczono maksymalny rozmiar macierzy!" << endl;
                return is;
            }
            
            if (znak != ' ') {
                cout << "Nieprawidłowy format danych!" << endl;
                return is;
            }
            
        }
        
        if (k != spr && spr != 0) {
            cout << "Ilosc kolumn w wierszach nie jest stala!" << endl;
            return is;
        }
        
        spr = k;
        
        wsk[w] = new double[k];
        
        for (k--; k >= 0; k--)
            wsk[w][k] = bufor[k];
        
        w++;
        k = 0;
        
        if (w > 10) {
            cout << "Przekroczono maksymalny rozmiar macierzy!" << endl;
            return is;
        }
        
        cin.get(znak);
        
        if (znak == '\n')
            break;
        else
            cin.putback(znak);
        
    }
    
    if (tmp.macierz != nullptr) {
        for (int i = 0; i < tmp.wiersze; i++)
            delete[] tmp.macierz[i];
        
        delete[] tmp.macierz;
    }
    
    tmp.wiersze = w;
    tmp.kolumny = spr;
    
    tmp.macierz = new double *[w];
    
    for (w--; w >= 0; w--)
        tmp.macierz[w] = wsk[w];
    
    return is;
}


#endif /* macierz_klas_h */
