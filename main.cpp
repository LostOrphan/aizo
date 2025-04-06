#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <windows.h>
//Uzyte metody sortowania: 
//
//Ustawienia wstępne
void ustawienia(int *tablicaRozmiar, int *dzialnieTryb, int *zakresGorny, int *zakresDolny){
    int input;
    while(input != 0){
        std::cout<<"[1] - Tryb dzialania programu\n";
        std::cout<<"[2] - Rozmiar tablicy\n";
        std::cout<<"[3] - Zakres generowania elementow tablicy\n";
        std::cout<<"[0] - Start programu\n";
        std::cin>>input;
        switch(input){
            case 1:
                std::cout<<"Wybierz tryb, w jakim ma dzialac program (domyslny tryb: pelny test): \n";
                std::cout<<"[1] - Pelny test \n";
                std::cout<<"[2] - ##SORT1##\n";
                std::cout<<"[3] - ##SORT2##\n";
                std::cout<<"[4] - ##SORT3##\n";
                std::cout<<"[5] - ##SORT4##\n";
                std::cout<<"[6] - ##BINSORT1##\n";
                std::cin>>*dzialnieTryb;
                if(std::cin.fail()){continue;}
                break;
            case 2:
                std::cout<<"Podaj rozmiar tablicy (domyslna wartosc: 100): ";
                std::cin>>*tablicaRozmiar;
                if(std::cin.fail()){continue;}
                break;
            case 3:
                std::cout<<"Podaj zakres dolny: ";
                std::cin>>*zakresDolny;
                if(std::cin.fail()){continue;}
                std::cout<<"Podaj zakres gorny: ";
                std::cin>>*zakresGorny;
                if(std::cin.fail()){continue;}
                break;
            default:
                break;
        }

    }
}
//wyzerowanie danych tablicy
//parametry: tablica - tablica do wyzerowania, tablicaRozmiar - rozmiar tablicy
void wyzerujTablice(int *tablica, int tablicaRozmiar){
    for(int i=0; i<tablicaRozmiar; i++){
        tablica[i]=0;
    }
}
//Wypelnianie tablicy tablicaRozmiar-elementowej losowymi wartosciami z zakresu <zakresDolny, zakresGorny>
//parametry: tablica - tablica do wypelnienia, tablicaRozmiar - rozmiar tablicy, zakresGorny - gorny zakres losowania, zakresDolny - dolny zakres losowania
//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
void wypelnijTablice(int *tablica, int tablicaRozmiar, int zakresGorny, int zakresDolny){
    wyzerujTablice(tablica, tablicaRozmiar);
    //generowanie danych tablicy
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(zakresDolny, zakresGorny);
    for(int i=0; i<tablicaRozmiar; i++){
        tablica[i]=distrib(gen);
    }
}
//parametry: zrodlo - tablica zrodlowa, cel - tablica docelowa, tablicaRozmiar - rozmiar tablicy
void skopiujTablice(int *zrodlo, int *cel, int tablicaRozmiar){
    wyzerujTablice(cel, tablicaRozmiar);
    for(int i=0; i<tablicaRozmiar; i++){
        cel[i]=zrodlo[i];
    }
}
//parametry: tablica - tablica do wypisania, tablicaRozmiar - rozmiar tablicy
void wypiszTablice(int *tablica, int tablicaRozmiar){
    for(int i=0; i<tablicaRozmiar; i++){
        std::cout<<tablica[i]<<" ";
    }
    std::cout<<"\n";
}
//Sortowanie przez wstawianie wstawiając od lewej strony tablicy oraz szukajac od prawej strony cześci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy
void sort1(int *tablica, int tablicaRozmiar){
    for(int i=1; i<tablicaRozmiar; i++){ 
        int x=tablica[i];
        int j=i-1; 
        while(j>=0 && x<tablica[j]){ 
            tablica[j+1]=tablica[j];
            j--;
        }
        tablica[j+1]=x;
    }
    
}
//Sortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od lewej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy
void sort2(int *tablica, int tablicaRozmiar){
    for (int i=tablicaRozmiar-2; i>=0; i--) {
        int x=tablica[i];
        int j=i+1;
        while (j<tablicaRozmiar && x>tablica[j]) {
            tablica[j-1]=tablica[j];
            j++;
        }
        tablica[j-1]=x;
    }
}
//Sortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od lewej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy
void sort3(int *tablica, int tablicaRozmiar){
    for (int i=1; i<tablicaRozmiar; i++) {
        int x=tablica[i];
        int wstaw=0;
        while (wstaw<i && tablica[wstaw]<=x) {
            wstaw++;
        }
        for (int j=i; j>wstaw; j--) {
            tablica[j]=tablica[j-1];
        }
        tablica[wstaw]=x;
    }
}
//Sortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od prawej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy
void sort4(int *tablica, int tablicaRozmiar){
    for (int i=tablicaRozmiar-2; i>=0; i--) {
        int x=tablica[i];
        int wstaw=tablicaRozmiar-1;
        while (wstaw>i && x<tablica[wstaw]) {
            wstaw--;
        }
        for(int j=i; j<wstaw; j++){
            tablica[j]=tablica[j+1];
        }
        tablica[wstaw]=x;
    }
}
//Pomocnicza funkcja dla binSort wykonujaca wyszukiwanie binarne i zwracajaca pozycje wstawienia elementu
//parametry: tablica - tablica do przeszukania, x - element do wstawienia, lewy - najmniejszy indeks posortowanej czesci, prawy - najwiekszy indeks posortowanej czesci
int wyszukiwanieBinarne(int *tablica, int x, int lewy, int prawy){
    while (lewy <= prawy) {
        int srodek=(lewy+prawy)/2;
        if (tablica[srodek]<x) {
            lewy=srodek+1;
        } else {
            prawy=srodek-1;
        }
    }
    return lewy;
}
//Sortowanie przez wstawianie wstawiając od lewej stronyoraz szukając poprzez wyszukiwanie binarne
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy
void binSort(int *tablica, int tablicaRozmiar){
    for (int i=1; i<tablicaRozmiar; i++) {
        int x=tablica[i];
        int wstaw=wyszukiwanieBinarne(tablica, x, 0, i-1);
        for (int j=i; j>wstaw; j--) {
            tablica[j]=tablica[j-1];
        }
        tablica[wstaw]=x;
    }
}
int main() {
    int tablicaRozmiar=10;
    int dzialnieTryb=1;
    int zakresGorny=100;
    int zakresDolny=1;
    int iloscProb=10;
   // ustawienia(&tablicaRozmiar, &dzialnieTryb, &zakresGorny, &zakresDolny);
    int tablicaZrodlo[tablicaRozmiar];
    int tablica[tablicaRozmiar];
    //Ustawienie zmiennych do pomiaru czasu
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    //Tablice zawierajace czasy sortowan
    double czasySort1[tablicaRozmiar];
    double czasySort2[tablicaRozmiar];
    double czasySort3[tablicaRozmiar];
    double czasySort4[tablicaRozmiar];
    double czasyBinSort[tablicaRozmiar];
    double czasSort1Srednia=0;
    double czasSort2Srednia=0;
    double czasSort3Srednia=0;
    double czasSort4Srednia=0;
    double czasBinSortSrednia=0;
    for(int i=0; i<iloscProb; i++){
        wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
        wypiszTablice(tablicaZrodlo, tablicaRozmiar);
        //sort1
        skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
        auto t1 = high_resolution_clock::now();
        sort1(tablica, tablicaRozmiar);
        auto t2 = high_resolution_clock::now();
        auto czasSort1 = duration<double, std::milli>(t2 - t1); 
        czasySort1[i]=czasSort1.count();
        czasSort1Srednia+=czasySort1[i];
        //wypisanie
        wypiszTablice(tablica, tablicaRozmiar);
        //sort2
        skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
        auto t3 = high_resolution_clock::now();
        sort2(tablica, tablicaRozmiar);
        auto t4 = high_resolution_clock::now();
        auto czasSort2 = duration<double, std::milli>(t4 - t3); 
        czasySort2[i]=czasSort2.count();
        czasSort2Srednia+=czasySort2[i];
        wypiszTablice(tablica, tablicaRozmiar);
        std::cout<<std::endl;
    }
    czasSort1Srednia=czasSort1Srednia/iloscProb;
    czasSort2Srednia=czasSort2Srednia/iloscProb;
    for(int i=0; i<iloscProb; i++){
        std::cout<<"Czas sortowania a" << czasySort1[i] << " milliseconds\n";
        std::cout<<"Czas sortowania b: " << czasySort2[i] << " milliseconds\n";
    }
    std::cout<<"Czas sortowania 1: " << czasSort1Srednia << " milliseconds\n";
    std::cout<<"Czas sortowania 2: " << czasSort2Srednia << " milliseconds\n";

    // wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
    
    // skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
    // wypiszTablice(tablicaZrodlo, tablicaRozmiar);
    // auto t1 = high_resolution_clock::now();
    // sort1(tablica, tablicaRozmiar);
    // wypiszTablice(tablica, tablicaRozmiar);
    // auto t2 = high_resolution_clock::now();


    // auto czasSort1 = duration_cast<milliseconds>(t2 - t1);
    // duration<double,std::milli> czasSort1=t2-t1;
    // czasySort1[0]=czasSort1.count();
    // skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
    // sort2(tablica, tablicaRozmiar);
    // wypiszTablice(tablica, tablicaRozmiar);

    // skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
    // sort3(tablica, tablicaRozmiar);
    // wypiszTablice(tablica, tablicaRozmiar);

    // skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
    // sort4(tablica, tablicaRozmiar);
    // wypiszTablice(tablica, tablicaRozmiar);

    // skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
    // binSort(tablica, tablicaRozmiar);
    // wypiszTablice(tablica, tablicaRozmiar);

    // std::cout<< "Czas sortowania 1: " << czasySort1[0] << " microseconds\n";
    return 0;
}