#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <windows.h>
#include <fstream>
//Uzyte metody sortowania: 
//
//Tryb programu
void tryb(int *dzialanieTryb){
    int input=10;
    while(input!=0){
        std::cout<<"[1] - Test czasowy \n";
        std::cout<<"[2] - Test dzialania \n";
        std::cout<<"[3] - Test pojedynczego sortowania \n";
        std::cout<<"[0] - Wyjscie \n";
        std::cin>>input;
        switch(input){
            case 1:
                *dzialanieTryb=1;
                return;
            case 2:
                *dzialanieTryb=2;
                return;
            case 3:
                std::cout<<"Wybierz sortowanie do przetestowania: \n";
                std::cout<<"[1] - Sort1 \n";
                std::cout<<"[2] - Sort2 \n";
                std::cout<<"[3] - Sort3 \n";
                std::cout<<"[4] - Sort4 \n";
                std::cout<<"[5] - BinSort \n";
                std::cout<<"[0] - Cofnij \n";
                std::cin>>input;
                if(input>=1||input<=5){
                    switch(input){
                        case 1:
                            *dzialanieTryb=3;
                            return;
                        case 2:
                            *dzialanieTryb=4;
                            return;
                        case 3:
                            *dzialanieTryb=5;
                            return;
                        case 4:
                            *dzialanieTryb=6;
                            return;
                        case 5:
                            *dzialanieTryb=7;
                            return;
                        case 0:
                            input=9;
                            break;
                        default:
                            std::cout<<"Niepoprawny wybor\n";
                    }
                    continue;
                }
                if(*dzialanieTryb>5){
                    std::cout<<"Niepoprawny wybor\n";
                    continue;
                }
                if(dzialanieTryb=0){continue;}
                return;
            case 0:
                exit(0);
            default:
                std::cout<<"Niepoprawny wybor\n";
                continue;
        }
    }
}
//Ustawienia wstępne
void ustawienia(int *dzialanieTryb, int  *tablicaRozmiar, int  *zakresGorny, int  *zakresDolny, int  *rozmiarPoczatkowy, int  *rozmiarZwieksz, int *rozmiarMax){
    int input;
    do{
    if(*dzialanieTryb!=1){
        std::cout<<"Podaj rozmiar tablicy: ";
        std::cin>>*tablicaRozmiar;
        std::cout<<"\n";
    }
    std::cout<<"Podaj dolny zakres losowania: ";
    std::cin>>*zakresDolny;
    std::cout<<"\n";
    std::cout<<"Podaj gorny zakres losowania: ";
    std::cin>>*zakresGorny;
    std::cout<<"\n";
    if(*dzialanieTryb==1){
        std::cout<<"Podaj rozmiar poczatkowy tablicy: ";
        std::cin>>*rozmiarPoczatkowy;
        std::cout<<"\n";
        std::cout<<"Podaj rozmiar przesuniecia tablicy: ";
        std::cin>>*rozmiarZwieksz;
        std::cout<<"\n";
        std::cout<<"Podaj maksymalny rozmiar tablicy: ";
        std::cin>>*rozmiarMax;
        std::cout<<"\n";
    }
    std::cout<<"Potwierdz ustawienia? [1] - Tak, [0] - Nie: "<<"\n";
    if(*dzialanieTryb!=1){
        std::cout<<"Rozmiar tablicy: "<<*tablicaRozmiar<<"\n";
    }
    std::cout<<"Zakres dolny losowania: "<<*zakresDolny<<"\n";
    std::cout<<"Zakres gorny losowania: "<<*zakresGorny<<"\n";
    if(*dzialanieTryb==1){
        std::cout<<"Rozmiar poczatkowy tablicy: "<<*rozmiarPoczatkowy<<"\n";
        std::cout<<"Wartosc zwiekszajaca rozmiar tablicy: "<<*rozmiarZwieksz<<"\n";
        std::cout<<"Maksymalny rozmiar tablicy: "<<*rozmiarMax<<"\n";
    }
    std::cin>>input;
    if(input==1){
        return;
    }
    else{
        std::cout<<"Wprowadz ustawienia ponownie\n";
    }
    }while(input!=1);
}
//wyzerowanie danych tablicy
//parametry: tablica - tablica do wyzerowania, tablicaRozmiar - rozmiar tablicy
void wyzerujTablice(int *tablica, int tablicaRozmiar){
    for(int i=0; i<tablicaRozmiar; i++){
        tablica[i]=0;
    }
}
//Wypelnianie tablicy tablicaRozmiar-elementowej losowymi wartosciami z zakresu <zakresDolny, zakresGorny>
//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
//parametry: tablica - tablica do wypelnienia, tablicaRozmiar - rozmiar tablicy, zakresGorny - gorny zakres losowania, zakresDolny - dolny zakres losowania
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
//Skopiowanie tablicy zrodlowej do tablicy docelowej
//parametry: zrodlo - tablica zrodlowa, cel - tablica docelowa, tablicaRozmiar - rozmiar tablicy
void skopiujTablice(int *zrodlo, int *cel, int tablicaRozmiar){
    wyzerujTablice(cel, tablicaRozmiar);
    for(int i=0; i<tablicaRozmiar; i++){
        cel[i]=zrodlo[i];
    }
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

//Funkcje sortowan z funkcja wypisywania do pliku
//Sortowanie przez wstawianie wstawiając od lewej strony tablicy oraz szukajac od prawej strony cześci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzestawien - ilosc przestawien
void sort1(int *tablica, int tablicaRozmiar, int iloscPorownan, int iloscPrzestawien){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    sortowania<<"\nSortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od prawej strony czesci posortowanej\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    for(int i=1; i<tablicaRozmiar; i++){ 
        int x=tablica[i];
        int j=i-1; 
        while(j>=0 && x<tablica[j]){ 
            iloscPorownan++;
            iloscPrzestawien++;
            sortowania<<"Zamiana na pozycji: "<<j+1<<" wartosc: "<<tablica[j+1]<<" z pozycja "<<j<<" wartosc: "<<tablica[j]<<"\n";
            tablica[j+1]=tablica[j];
            j--;
        }
        tablica[j+1]=x;
        sortowania<<"Zamiana na pozycji: "<<j+1<<" wartosc:"<<tablica[j+1]<<" na wartosc: "<<x<<"\n";
        iloscPrzestawien++;
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania<<"Ilosc porownan: "<<iloscPorownan<<"\n";
    sortowania<<"Ilosc przestawien: "<<iloscPrzestawien<<"\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    sortowania.close();
}
//Sortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od lewej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzestawien - ilosc przestawien
void sort2(int *tablica, int tablicaRozmiar, int iloscPorownan, int iloscPrzestawien){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    sortowania<<"\nSortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od lewej strony czesci posortowanej\n";
    for (int i=tablicaRozmiar-2; i>=0; i--) {
        int x=tablica[i];
        int j=i+1;
        while (j<tablicaRozmiar && x>tablica[j]) {
            iloscPorownan++;
            iloscPrzestawien++;
            sortowania<<"Zamiana na pozycji: "<<j-1<<" wartosc: "<<tablica[j-1]<<" z pozycja "<<j<<" wartosc: "<<tablica[j]<<"\n";
            tablica[j-1]=tablica[j];
            j++;
        }
        tablica[j-1]=x;
        sortowania<<"Zamiana na pozycji: "<<j<<" wartosc:"<<tablica[j-1]<<" na wartosc: "<<x<<"\n";
        iloscPrzestawien++;
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania<<"Ilosc porownan: "<<iloscPorownan<<"\n";
    sortowania<<"Ilosc przestawien: "<<iloscPrzestawien<<"\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    sortowania.close();
}
//Sortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od lewej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzestawien - ilosc przestawien
void sort3(int *tablica, int tablicaRozmiar, int iloscPorownan, int iloscPrzestawien){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    sortowania<<"\nSortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od lewej strony czesci posortowanej\n";
    for (int i=1; i<tablicaRozmiar; i++) {
        int x=tablica[i];
        int wstaw=0;
        while (wstaw<i && tablica[wstaw]<=x) {
            iloscPorownan++;
            wstaw++;
        }
        for (int j=i; j>wstaw; j--) {
            iloscPrzestawien++;
            sortowania<<"Zamiana na pozycji: "<<j<<" wartosc: "<<tablica[j]<<" z pozycja "<<j-1<<" wartosc: "<<tablica[j-1]<<"\n";
            tablica[j]=tablica[j-1];
        }
        tablica[wstaw]=x;
        sortowania<<"Zamiana na pozycji: "<<wstaw<<" wartosc:"<<tablica[wstaw]<<" na wartosc: "<<x<<"\n";
        iloscPrzestawien++;
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania<<"Ilosc porownan: "<<iloscPorownan<<"\n";
    sortowania<<"Ilosc przestawien: "<<iloscPrzestawien<<"\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    sortowania.close();
}
//Sortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od prawej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzestawien - ilosc przestawien
void sort4(int *tablica, int tablicaRozmiar, int iloscPorownan, int iloscPrzestawien){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    sortowania<<"\nSortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od prawej strony czesci posortowanej\n";
    for (int i=tablicaRozmiar-2; i>=0; i--) {
        int x=tablica[i];
        int wstaw=tablicaRozmiar-1;
        while (wstaw>i && x<tablica[wstaw]) {
            iloscPorownan++;
            wstaw--;
        }
        for(int j=i; j<wstaw; j++){
            iloscPrzestawien++;
            sortowania<<"Zamiana na pozycji: "<<j<<" wartosc: "<<tablica[j]<<" z pozycja "<<j+1<<" wartosc: "<<tablica[j+1]<<"\n";
            tablica[j]=tablica[j+1];
        }
        tablica[wstaw]=x;
        sortowania<<"Zamiana na pozycji: "<<wstaw<<" wartosc:"<<tablica[wstaw]<<" na wartosc: "<<x<<"\n";
        iloscPrzestawien++;
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania<<"Ilosc porownan: "<<iloscPorownan<<"\n";
    sortowania<<"Ilosc przestawien: "<<iloscPrzestawien<<"\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    sortowania.close();
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
}int wyszukiwanieBinarne(int *tablica, int x, int lewy, int prawy, int *iloscPorownan){
    while (lewy <= prawy) {
        int srodek=(lewy+prawy)/2;
        if (tablica[srodek]<x) {
            (*iloscPorownan)++;
            lewy=srodek+1;
        } else {
            (*iloscPorownan)++;
            prawy=srodek-1;
        }
    }
    return lewy;
}
//Sortowanie przez wstawianie wstawiając od lewej stronym oraz szukając poprzez wyszukiwanie binarne
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
//Sortowanie przez wstawianie wstawiając od lewej stronym oraz szukając poprzez wyszukiwanie binarne
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzestawien - ilosc przestawien
void binSort(int *tablica, int tablicaRozmiar, int iloscPorownan, int iloscPrzestawien){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    sortowania<<"\nSortowanie przez wstawianie wstawiajac od lewej stronym oraz szukając poprzez wyszukiwanie binarne\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    for (int i=1; i<tablicaRozmiar; i++) {
        int x=tablica[i];
        int wstaw=wyszukiwanieBinarne(tablica, x, 0, i-1, &iloscPorownan);
        for (int j=i; j>wstaw; j--) {
            iloscPrzestawien++;
            sortowania<<"Zamiana na pozycji: "<<j<<" wartosc: "<<tablica[j]<<" z pozycja "<<j-1<<" wartosc: "<<tablica[j-1]<<"\n";
            tablica[j]=tablica[j-1];
        }
        tablica[wstaw]=x;
        sortowania<<"Zamiana na pozycji: "<<wstaw<<" wartosc:"<<tablica[wstaw]<<" na wartosc: "<<x<<"\n";
        iloscPrzestawien++;
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania<<"Ilosc porownan: "<<iloscPorownan<<"\n";
    sortowania<<"Ilosc przestawien: "<<iloscPrzestawien<<"\n";
    sortowania<<"-----------------------------------------------------------------------------------\n";
    sortowania.close();
}
//Funkcja wypisujaca wyniki do pliku wyniki.txt
//parametry: czasySort1 - czasy sortowania 1, czasySort2 - czasy sortowania 2, czasySort3 - czasy sortowania 3, czasySort4 - czasy sortowania 4, czasyBinSort - czasy binSort, rozmiarDanych - rozmiar danych, iloscDanych - ilosc danych
void wypisanieWynikow(double *czasySort1, double *czasySort2, double *czasySort3, double *czasySort4, double *czasyBinSort, int *rozmiarDanych, int iloscDanych){
    std::ofstream wyniki("wyniki.txt");
    if(wyniki.is_open()){
        for (int i=0;i<iloscDanych;i++){
            //int j=0;
            wyniki <<rozmiarDanych[i]  << ";" << czasySort1[i] << ";" << czasySort2[i] << ";" << czasySort3[i] << ";" << czasySort4[i] << ";" << czasyBinSort[i] << "\n";
            //j++;
        }
        wyniki.close();
    }
}
//Funkcja wypisujaca tablice do pliku sortowania.txt
//parametry: tablica - tablica do wypisania, tablicaRozmiar - rozmiar tablicy
void wypiszTablice(int *tablica, int tablicaRozmiar){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    if(sortowania.is_open()){
        sortowania<<"Tablica\n";
        for (int i=0;i<tablicaRozmiar;i++){
            sortowania <<i<<": "<<tablica[i] << " | ";
        }
        sortowania.close();
    }
}
//Funkcja uzyta do wykonania testow zamieszczonych w sprawozdaniu
//Rozmiar tablicy z kazda now
void testCzas(int tablicaRozmiar, int zakresGorny, int zakresDolny, int iloscProb, int rozmiarPoczatkowy, int rozmiarZwieksz, int rozmiarMax){
    //Ustawienie zmiennych do pomiaru czasu
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    double czasSort1Srednia=0;
    double czasSort2Srednia=0;
    double czasSort3Srednia=0;
    double czasSort4Srednia=0;
    double czasBinSortSrednia=0;
    std::vector<double> czasySort1;
    std::vector<double> czasySort2;
    std::vector<double> czasySort3;
    std::vector<double> czasySort4;
    std::vector<double> czasyBinSort;
    std::vector<int> rozmiarDanych; 
    for(int i=rozmiarPoczatkowy;i<=rozmiarMax;i+=rozmiarZwieksz){
        rozmiarDanych.push_back(i);
        tablicaRozmiar=i;
        int *tablicaZrodlo=new int[tablicaRozmiar];
        int *tablica=new int[tablicaRozmiar];
        for(int j=0;j<iloscProb;j++){
            //Wypelnienie tablicy zrodlowej
            wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
            //Wyzerowanie zmiennych od czasow srednich
            czasSort1Srednia=0;
            czasSort2Srednia=0;
            czasSort3Srednia=0;
            czasSort4Srednia=0;
            czasBinSortSrednia=0;
            //sort1
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t1 = high_resolution_clock::now();
            sort1(tablica, tablicaRozmiar);
            auto t2 = high_resolution_clock::now();
            auto czasSort1 = duration<double, std::milli>(t2 - t1); 
            czasSort1Srednia+=czasSort1.count();
            //sort2
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t3 = high_resolution_clock::now();
            sort2(tablica, tablicaRozmiar);
            auto t4 = high_resolution_clock::now();
            auto czasSort2 = duration<double, std::milli>(t4 - t3);
            czasSort2Srednia+=czasSort2.count();
            //sort3
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t5 = high_resolution_clock::now();
            sort3(tablica, tablicaRozmiar);
            auto t6 = high_resolution_clock::now();
            auto czasSort3 = duration<double, std::milli>(t6 - t5);
            czasSort3Srednia+=czasSort3.count();
            //sort4
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t7 = high_resolution_clock::now();
            sort4(tablica, tablicaRozmiar);
            auto t8 = high_resolution_clock::now();
            auto czasSort4 = duration<double, std::milli>(t8 - t7);
            czasSort4Srednia+=czasSort4.count();
            //binSort
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t9 = high_resolution_clock::now();
            binSort(tablica, tablicaRozmiar);
            auto t10 = high_resolution_clock::now();
            auto czasBinSort = duration<double, std::milli>(t10 - t9);
            czasBinSortSrednia+=czasBinSort.count();
        }
        //Wpisanie wynikow do tablicy
        czasySort1.push_back(czasSort1Srednia/iloscProb);
        czasySort2.push_back(czasSort2Srednia/iloscProb);
        czasySort3.push_back(czasSort3Srednia/iloscProb);
        czasySort4.push_back(czasSort4Srednia/iloscProb);
        czasyBinSort.push_back(czasBinSortSrednia/iloscProb);

        delete[] tablica;
        delete[] tablicaZrodlo;
        std::cout<<"Ukonczono test dla rozmiaru: "<<tablicaRozmiar<<std::endl;
    }
    wypisanieWynikow(czasySort1.data(), czasySort2.data(), czasySort3.data(), czasySort4.data(), czasyBinSort.data(), rozmiarDanych.data(), rozmiarDanych.size());
}
void testDzialanie(int tablicaRozmiar, int zakresGorny, int zakresDolny, int iloscPorownan, int iloscPrzestawien){
    int *tablicaZrodlo=new int[tablicaRozmiar];
    int *tablica=new int[tablicaRozmiar];
    wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
    std::ofstream sortowania("sortowania.txt");
    sortowania.close();
    wypiszTablice(tablicaZrodlo, tablicaRozmiar);
    for(int i=1;i<=5;i++){
        skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
        switch(i){
            case 1:
                iloscPorownan=0;
                iloscPrzestawien=0;
                sort1(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestawien);
                break;
            case 2:
                iloscPorownan=0;
                iloscPrzestawien=0;
                sort2(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestawien);
                break;
            case 3:
                iloscPorownan=0;
                iloscPrzestawien=0;
                sort3(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestawien);
                break;
            case 4:
                iloscPorownan=0;
                iloscPrzestawien=0;
                sort4(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestawien);
                break;
            case 5:
                iloscPorownan=0;
                iloscPrzestawien=0;
                binSort(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestawien);
                break;
        }
        wypiszTablice(tablica, tablicaRozmiar);
        std::cout<<"Ukonczono test nr: "<<i<<" z 5"<<std::endl;
    }
}
int main() {
    int tablicaRozmiar=10;
    int dzialanieTryb=1;
    int zakresGorny=100;
    int zakresDolny=1;
    int iloscProb=10;

    int rozmiarPoczatkowy=10;
    int rozmiarZwieksz=10;
    int rozmiarMax=100;

    int iloscPorownan=0;
    int iloscPrzestaien=0;
    tryb(&dzialanieTryb);
    ustawienia(&dzialanieTryb, &tablicaRozmiar, &zakresGorny, &zakresDolny, &rozmiarPoczatkowy, &rozmiarZwieksz, &rozmiarMax);
    switch(dzialanieTryb){
        case 1:
            testCzas(tablicaRozmiar, zakresGorny, zakresDolny, iloscProb, rozmiarPoczatkowy, rozmiarZwieksz, rozmiarMax);
            break;
        case 2:
            testDzialanie(tablicaRozmiar, zakresGorny, zakresDolny, iloscPorownan, iloscPrzestaien);
            break;
        case 3: {
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sort1(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestaien);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 4:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sort2(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestaien);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 5:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sort3(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestaien);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 6:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sort4(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestaien);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 7:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            binSort(tablica, tablicaRozmiar, iloscPorownan, iloscPrzestaien);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
    }

    return 0;
}