#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <fstream>
//Tryb programu
void tryb(int *dzialanieTryb, int *wypisz){
    int input=10;
    while(input!=0){
        std::cout<<"[1] - Test czasowy \n";
        std::cout<<"[2] - Test dzialania \n";
        std::cout<<"[3] - Test ilosci porownan i przesuniec\n";
        std::cout<<"[4] - Test pojedynczego sortowania \n";
        std::cout<<"[0] - Wyjscie \n";
        std::cin>>input;
        switch(input){
            case 1:
                *dzialanieTryb=1;
                return;
            case 2:
                *dzialanieTryb=2;
                *wypisz=1;
                return;
            case 3:
                *dzialanieTryb=3;
                return;
            case 4:
                std::cout<<"Wybierz sortowanie do przetestowania: \n";
                std::cout<<"[1] - sortLP \n";
                std::cout<<"[2] - sortPL \n";
                std::cout<<"[3] - sortLL \n";
                std::cout<<"[4] - sortPP \n";
                std::cout<<"[5] - BinSort \n";
                std::cout<<"[6] - reverse sortLP \n";
                std::cout<<"[0] - Cofnij \n";
                std::cin>>input;
                if(input>=1||input<=5){
                    switch(input){
                        case 1:
                            *dzialanieTryb=41;
                            *wypisz=1;
                            return;
                        case 2:
                            *dzialanieTryb=42;
                            *wypisz=1;
                            return;
                        case 3:
                            *dzialanieTryb=43;
                            *wypisz=1;
                            return;
                        case 4:
                            *dzialanieTryb=44;
                            *wypisz=1;
                            return;
                        case 5:
                            *dzialanieTryb=45;
                            *wypisz=1;
                            return;
                        case 6:
                            *dzialanieTryb=46;
                            *wypisz=1;
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
        std::cout<<"Podaj rozmiar zwiekszenia rozmiaru tablicy: ";
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
void sortLP(int *tablica, int tablicaRozmiar){
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
void sortPL(int *tablica, int tablicaRozmiar){
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
void sortLL(int *tablica, int tablicaRozmiar){
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
void sortPP(int *tablica, int tablicaRozmiar){
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
//
//Funkcje sortowan z funkcja wypisywania do pliku
//


//Sortowanie przez wstawianie wstawiając od lewej strony tablicy oraz szukajac od prawej strony cześci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzesuniec - ilosc Przesuniec
void sortLP(int *tablica, int tablicaRozmiar, long long  *iloscPorownan, long long  *iloscPrzesuniec, int wypisz){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    if(wypisz==1){
        sortowania<<"\nSortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od prawej strony czesci posortowanej\n";
    }
    for(int i=1; i<tablicaRozmiar; i++){ 
        int x=tablica[i];
        int j=i-1; 
        // (*iloscPorownan)++;
        while(j>=0 && x<tablica[j]){ 
            if(wypisz==1){
                sortowania<<"Zamiana na pozycji: "<<j+1<<" wartosc: "<<tablica[j+1]<<" z pozycja "<<j<<" wartosc: "<<tablica[j]<<"\n";
            }
            tablica[j+1]=tablica[j];
            (*iloscPrzesuniec)++;
            (*iloscPorownan)++;
            j--;
        }
        (*iloscPorownan)++;
        tablica[j+1]=x;
        (*iloscPrzesuniec)++;
        if(wypisz==1){   
            sortowania<<"Zamiana na pozycji: "<<j+1<<" wartosc:"<<tablica[j+1]<<" na wartosc: "<<x<<"\n";
            sortowania<<"-----------------------------------------------------------------------------------\n";
        }
    }
    if(wypisz==1){
        sortowania<<"Ilosc porownan: "<<*iloscPorownan<<"\n";
        sortowania<<"Ilosc Przesuniec: "<<*iloscPrzesuniec<<"\n";
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania.close();
}
//Sortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od lewej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzesuniec - ilosc Przesuniec
void sortPL(int *tablica, int tablicaRozmiar, long long  *iloscPorownan, long long  *iloscPrzesuniec, int wypisz){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    if(wypisz==1){
        sortowania<<"\nSortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od lewej strony czesci posortowanej\n";
    }
    for (int i=tablicaRozmiar-2; i>=0; i--) {
        int x=tablica[i];
        int j=i+1;
        while (j<tablicaRozmiar && x>tablica[j]) {
            if(wypisz==1){
                sortowania<<"Zamiana na pozycji: "<<j-1<<" wartosc: "<<tablica[j-1]<<" z pozycja "<<j<<" wartosc: "<<tablica[j]<<"\n";
            }
            tablica[j-1]=tablica[j];
            (*iloscPorownan)++;
            (*iloscPrzesuniec)++;
            j++;
        }
        (*iloscPorownan)++;
        tablica[j-1]=x;
        (*iloscPrzesuniec)++;
        if(wypisz==1){   
            sortowania<<"Zamiana na pozycji: "<<j-1<<" wartosc:"<<tablica[j-1]<<" na wartosc: "<<x<<"\n";
            sortowania<<"-----------------------------------------------------------------------------------\n";
        }
    }
    if(wypisz==1){
        sortowania<<"Ilosc porownan: "<<*iloscPorownan<<"\n";
        sortowania<<"Ilosc Przesuniec: "<<*iloscPrzesuniec<<"\n";
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania.close();
}
//Sortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od lewej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzesuniec - ilosc Przesuniec
void sortLL(int *tablica, int tablicaRozmiar, long long  *iloscPorownan, long long  *iloscPrzesuniec, int wypisz){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    if(wypisz==1){
        sortowania<<"\nSortowanie przez wstawianie wstawiajac od lewej strony tablicy oraz szukajac od lewej strony czesci posortowanej\n";
    }
    for (int i=1; i<tablicaRozmiar; i++) {
        int x=tablica[i];
        int wstaw=0;
        while (wstaw<i && tablica[wstaw]<=x) {
            (*iloscPorownan)++;
            wstaw++;
        }
        (*iloscPorownan)++;
        for (int j=i; j>wstaw; j--) {
            if(wypisz==1){
                sortowania<<"Zamiana na pozycji: "<<j<<" wartosc: "<<tablica[j]<<" z pozycja "<<j-1<<" wartosc: "<<tablica[j-1]<<"\n";
            }
            tablica[j]=tablica[j-1];
            (*iloscPrzesuniec)++;
        }
        tablica[wstaw]=x;
        (*iloscPrzesuniec)++;
        if(wypisz==1){
            sortowania<<"Zamiana na pozycji: "<<wstaw<<" wartosc:"<<tablica[wstaw]<<" na wartosc: "<<x<<"\n";
            sortowania<<"-----------------------------------------------------------------------------------\n";
        }
    }
    if(wypisz==1){
        sortowania<<"Ilosc porownan: "<<*iloscPorownan<<"\n";
        sortowania<<"Ilosc Przesuniec: "<<*iloscPrzesuniec<<"\n";
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania.close();
}
//Sortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od prawej strony czesci posortowanej
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzesuniec - ilosc Przesuniec
void sortPP(int *tablica, int tablicaRozmiar, long long  *iloscPorownan, long long  *iloscPrzesuniec, int wypisz){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    if(wypisz==1){
        sortowania<<"\nSortowanie przez wstawianie wstawiajac od prawej strony tablicy oraz szukajac od prawej strony czesci posortowanej\n";
    }
    for (int i=tablicaRozmiar-2; i>=0; i--) {
        int x=tablica[i];
        int wstaw=tablicaRozmiar-1;
        while (wstaw>i && x<tablica[wstaw]) {
            (*iloscPorownan)++;
            wstaw--;
        }
        (*iloscPorownan)++;
        for(int j=i; j<wstaw; j++){
            if(wypisz==1){
                sortowania<<"Zamiana na pozycji: "<<j<<" wartosc: "<<tablica[j]<<" z pozycja "<<j+1<<" wartosc: "<<tablica[j+1]<<"\n";
            }
            tablica[j]=tablica[j+1];
            (*iloscPrzesuniec)++;
        }
        tablica[wstaw]=x;
        (*iloscPrzesuniec)++;
        if(wypisz==1){
            sortowania<<"Zamiana na pozycji: "<<wstaw<<" wartosc:"<<tablica[wstaw]<<" na wartosc: "<<x<<"\n";
            sortowania<<"-----------------------------------------------------------------------------------\n";
        }
    }
    if(wypisz==1){
        sortowania<<"Ilosc porownan: "<<*iloscPorownan<<"\n";
        sortowania<<"Ilosc Przesuniec: "<<*iloscPrzesuniec<<"\n";
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
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
}int wyszukiwanieBinarne(int *tablica, int x, int lewy, int prawy, long long  *iloscPorownan){
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
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy, iloscPorownan - ilosc porownan, iloscPrzesuniec - ilosc Przesuniec
void binSort(int *tablica, int tablicaRozmiar, long long  *iloscPorownan, long long  *iloscPrzesuniec, int wypisz){
    std::ofstream sortowania("sortowania.txt", std::ios::app);
    if(wypisz==1){
        sortowania<<"\nSortowanie przez wstawianie wstawiajac od lewej stronym oraz szukając poprzez wyszukiwanie binarne\n";
    }
    for (int i=1; i<tablicaRozmiar; i++) {
        int x=tablica[i];
        int wstaw=wyszukiwanieBinarne(tablica, x, 0, i-1, iloscPorownan);
        for (int j=i; j>wstaw; j--) {
            if(wypisz==1){
                sortowania<<"Zamiana na pozycji: "<<j<<" wartosc: "<<tablica[j]<<" z pozycja "<<j-1<<" wartosc: "<<tablica[j-1]<<"\n";
            }
            tablica[j]=tablica[j-1];
            (*iloscPrzesuniec)++;
        }
        tablica[wstaw]=x;
        (*iloscPrzesuniec)++;
        if(wypisz==1){
            sortowania<<"Zamiana na pozycji: "<<wstaw<<" wartosc:"<<tablica[wstaw]<<" na wartosc: "<<x<<"\n";
            sortowania<<"-----------------------------------------------------------------------------------\n";
        }
    }
    if(wypisz==1){
        sortowania<<"Ilosc porownan: "<<*iloscPorownan<<"\n";
        sortowania<<"Ilosc Przesuniec: "<<*iloscPrzesuniec<<"\n";
        sortowania<<"-----------------------------------------------------------------------------------\n";
    }
    sortowania.close();
}
//Pomocnicze sortowanie przez wstawianie sortujac liczby malejaca
//parametry: tablica - tablica do posortowania, tablicaRozmiar - rozmiar tablicy
void sortReverse(int *tablica, int tablicaRozmiar){
    for(int i=1; i<tablicaRozmiar; i++){ 
        int x=tablica[i];
        int j=i-1; 
        while(j>=0 && x>tablica[j]){ 
            tablica[j+1]=tablica[j];
            j--;
        }
        tablica[j+1]=x;
    }
}
//Funkcja wypisujaca wyniki do pliku wyniki.txt
//parametry: czasysortLP - czasy sortowania 1, czasysortPL - czasy sortowania 2, czasysortLL - czasy sortowania 3, czasysortPP - czasy sortowania 4, czasyBinSort - czasy binSort, rozmiarDanych - rozmiar danych, iloscDanych - ilosc danych
void wypisanieWynikow(double *czasysortLP, double *czasysortPL, double *czasysortLL, double *czasysortPP, double *czasyBinSort, int *rozmiarDanych, int iloscDanych){
    std::ofstream wyniki("wyniki.txt");
    wyniki<<"Rozmiar tablicy;Czas sortLP;Czas sortPL;Czas sortLL;Czas sortPP;Czas binSort\n";
    if(wyniki.is_open()){
        for (int i=0;i<iloscDanych;i++){
            //int j=0;
            wyniki <<rozmiarDanych[i]  << ";" << czasysortLP[i] << ";" << czasysortPL[i] << ";" << czasysortLL[i] << ";" << czasysortPP[i] << ";" << czasyBinSort[i] << "\n";
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
    double czassortLPSrednia=0;
    double czassortPLSrednia=0;
    double czassortLLSrednia=0;
    double czassortPPSrednia=0;
    double czasBinSortSrednia=0;
    std::vector<double> czasysortLP;
    std::vector<double> czasysortPL;
    std::vector<double> czasysortLL;
    std::vector<double> czasysortPP;
    std::vector<double> czasyBinSort;
    std::vector<int> rozmiarDanych; 
    for(int i=rozmiarPoczatkowy;i<=rozmiarMax;i+=rozmiarZwieksz){
        rozmiarDanych.push_back(i);
        tablicaRozmiar=i;
        int *tablicaZrodlo=new int[tablicaRozmiar];
        int *tablica=new int[tablicaRozmiar];
        //Wyzerowanie zmiennych od czasow srednich
        czassortLPSrednia=0;
        czassortPLSrednia=0;
        czassortLLSrednia=0;
        czassortPPSrednia=0;
        czasBinSortSrednia=0;
        for(int j=0;j<iloscProb;j++){
            //Wypelnienie tablicy zrodlowej
            wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
            //sortLP
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t1 = high_resolution_clock::now();
            sortLP(tablica, tablicaRozmiar);
            auto t2 = high_resolution_clock::now();
            auto czassortLP = duration<double, std::milli>(t2 - t1); 
            czassortLPSrednia+=czassortLP.count();
            //sortPL
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t3 = high_resolution_clock::now();
            sortPL(tablica, tablicaRozmiar);
            auto t4 = high_resolution_clock::now();
            auto czassortPL = duration<double, std::milli>(t4 - t3);
            czassortPLSrednia+=czassortPL.count();
            //sortLL
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t5 = high_resolution_clock::now();
            sortLL(tablica, tablicaRozmiar);
            auto t6 = high_resolution_clock::now();
            auto czassortLL = duration<double, std::milli>(t6 - t5);
            czassortLLSrednia+=czassortLL.count();
            //sortPP
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t7 = high_resolution_clock::now();
            sortPP(tablica, tablicaRozmiar);
            auto t8 = high_resolution_clock::now();
            auto czassortPP = duration<double, std::milli>(t8 - t7);
            czassortPPSrednia+=czassortPP.count();
            //binSort
            skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
            auto t9 = high_resolution_clock::now();
            binSort(tablica, tablicaRozmiar);
            auto t10 = high_resolution_clock::now();
            auto czasBinSort = duration<double, std::milli>(t10 - t9);
            czasBinSortSrednia+=czasBinSort.count();
        }
        //Wpisanie wynikow do tablicy
        czasysortLP.push_back(czassortLPSrednia/iloscProb);
        czasysortPL.push_back(czassortPLSrednia/iloscProb);
        czasysortLL.push_back(czassortLLSrednia/iloscProb);
        czasysortPP.push_back(czassortPPSrednia/iloscProb);
        czasyBinSort.push_back(czasBinSortSrednia/iloscProb);

        delete[] tablica;
        delete[] tablicaZrodlo;
        std::cout<<"Ukonczono test dla rozmiaru: "<<tablicaRozmiar<<std::endl;
    }
    wypisanieWynikow(czasysortLP.data(), czasysortPL.data(), czasysortLL.data(), czasysortPP.data(), czasyBinSort.data(), rozmiarDanych.data(), rozmiarDanych.size());
}
void testDzialanie(int tablicaRozmiar, int zakresGorny, int zakresDolny, long long  &iloscPorownan, long long  iloscPrzesuniec, int wypisz){
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
                iloscPrzesuniec=0;
                sortLP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                break;
            case 2:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                break;
            case 3:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                break;
            case 4:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                break;
            case 5:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                binSort(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                break;
        }
        wypiszTablice(tablica, tablicaRozmiar);
        std::cout<<"Ukonczono test nr: "<<i<<" z 5"<<std::endl;
    }
}
void testPorownan(int tablicaRozmiar, int zakresGorny, int zakresDolny, long long  iloscPorownan, long long  iloscPrzesuniec, int wypisz){
    int *tablicaZrodlo=new int[tablicaRozmiar];
    int *tablica=new int[tablicaRozmiar];
    std::ofstream sortowania("sortowania.txt");
    //Test na tablicy posortowanej rosnaco
    wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
    sortLP(tablicaZrodlo, tablicaRozmiar);
    sortowania<<"Test tablicy posortowanej rosnaco\n";
    for(int i=0;i<=5;i++){
        skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
        switch(i){
            case 0:
                sortowania<<"\nsortLP\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 1:
                sortowania<<"sortPL\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 2:
                sortowania<<"sortLL\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 3: 
                sortowania<<"sortPP\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 4:
                sortowania<<"binSort\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                binSort(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
        }
    }
    //Test na tablicy posortowanej malejaco
    sortReverse(tablicaZrodlo, tablicaRozmiar);
    sortowania<<"\nTest tablicy posortowanej malejaco\n";
    for(int i=0;i<=5;i++){
        skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
        switch(i){
            case 0:
                sortowania<<"sortLP\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 1:
                sortowania<<"sortPL\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 2:
                sortowania<<"sortLL\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 3: 
                sortowania<<"sortPP\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
            case 4:
                sortowania<<"binSort\n";
                iloscPorownan=0;
                iloscPrzesuniec=0;
                binSort(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                sortowania<<"   Ilosc porownan: "<<iloscPorownan<<"\n";
                sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniec<<"\n";
                break;
        }
    }
    //Test na tablicy posortowanej losowo (sredni wynik ze 100 prob)
    double iloscPorownanSrednia[5]={0,0,0,0,0};
    double iloscPrzesuniecSrednia[5]={0,0,0,0,0};
    for(int i=0;i<100;i++){
        wyzerujTablice(tablicaZrodlo, tablicaRozmiar);
        wypelnijTablice(tablicaZrodlo, tablicaRozmiar, zakresGorny, zakresDolny);
      for(int j=0;j<5;j++){
        skopiujTablice(tablicaZrodlo, tablica, tablicaRozmiar);
        switch(j){
            case 0:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                iloscPorownanSrednia[j]+=iloscPorownan;
                iloscPrzesuniecSrednia[j]+=iloscPrzesuniec;
                break;
            case 1:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                iloscPorownanSrednia[j]+=iloscPorownan;
                iloscPrzesuniecSrednia[j]+=iloscPrzesuniec;
                break;
            case 2:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortLL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                iloscPorownanSrednia[j]+=iloscPorownan;
                iloscPrzesuniecSrednia[j]+=iloscPrzesuniec;
                break;
            case 3: 
                iloscPorownan=0;
                iloscPrzesuniec=0;
                sortPP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                iloscPorownanSrednia[j]+=iloscPorownan;
                iloscPrzesuniecSrednia[j]+=iloscPrzesuniec;
                break;
            case 4:
                iloscPorownan=0;
                iloscPrzesuniec=0;
                binSort(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
                iloscPorownanSrednia[j]+=iloscPorownan;
                iloscPrzesuniecSrednia[j]+=iloscPrzesuniec;
                break;
        }
      }
    }
    //Srednia wynikow
    for(int i=0;i<5;i++){
        iloscPorownanSrednia[i]/=100;
        iloscPrzesuniecSrednia[i]/=100;
    }
    //Wypisanie wynikow do pliku
    sortowania<<"\nTest tablicy posortowanej losowo (srednia ze 100 prob)\n";
    for(int i=0;i<5;i++){
        switch(i){
            case 0:
                sortowania<<"sortLP\n";
                break;
            case 1:
                sortowania<<"sortPL\n";
                break;
            case 2:
                sortowania<<"sortLL\n";
                break;
            case 3: 
                sortowania<<"sortPP\n";
                break;
            case 4:
                sortowania<<"binSort\n";
                break;
        }
        sortowania<<"   Ilosc porownan: "<<iloscPorownanSrednia[i]<<"\n";
        sortowania<<"   Ilosc Przesuniec: "<<iloscPrzesuniecSrednia[i]<<"\n";
    }
    sortowania.close();
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

    int wypisz=0;
    long long  iloscPorownan=0;
    long long  iloscPrzesuniec=0;
    tryb(&dzialanieTryb,&wypisz);
    ustawienia(&dzialanieTryb, &tablicaRozmiar, &zakresGorny, &zakresDolny, &rozmiarPoczatkowy, &rozmiarZwieksz, &rozmiarMax);
    switch(dzialanieTryb){
        case 1:
            testCzas(tablicaRozmiar, zakresGorny, zakresDolny, iloscProb, rozmiarPoczatkowy, rozmiarZwieksz, rozmiarMax);
            break;
        case 2:
            testDzialanie(tablicaRozmiar, zakresGorny, zakresDolny, iloscPorownan, iloscPrzesuniec, wypisz);
            break;
        case 3:{
            testPorownan(tablicaRozmiar, zakresGorny, zakresDolny, iloscPorownan, iloscPrzesuniec, wypisz);
            break;

        }
        case 41: {
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sortLP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 42:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sortPL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 43:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sortLL(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 44:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sortPP(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 45:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            binSort(tablica, tablicaRozmiar, &iloscPorownan, &iloscPrzesuniec, wypisz);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
        case 46:{
            int *tablica=new int[tablicaRozmiar];
            std::ofstream sortowania("sortowania.txt");
            sortowania.close();
            wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
            wypiszTablice(tablica, tablicaRozmiar);
            sortReverse(tablica, tablicaRozmiar);
            wypiszTablice(tablica, tablicaRozmiar);
            delete[] tablica;
            break;
        }
    }

    return 0;
}