#include <iostream>
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
//Wypelnianie tablicy tablicaRozmiar-elementowej losowymi wartosciami z zakresu <zakresDolny, zakresGorny>
void wypelnijTablice(int *tablica, int tablicaRozmiar, int zakresGorny, int zakresDolny){
    //wyzerowanie danych tablicy
    std::fill(tablica, tablica + tablicaRozmiar, 0);
    //generowanie danych tablicy
    for(int i = 0; i < tablicaRozmiar; i++){
        tablica[i] = rand() % (zakresGorny - zakresDolny + 1) + zakresDolny;
    }
}

int main() {
    int tablicaRozmiar=100;
    int dzialnieTryb=1;
    int zakresGorny;
    int zakresDolny;
    ustawienia(&tablicaRozmiar, &dzialnieTryb, &zakresGorny, &zakresDolny);
    int tablica[tablicaRozmiar];
    for(int i=0;i<100;i++){
    wypelnijTablice(tablica, tablicaRozmiar, zakresGorny, zakresDolny);
    for(int i = 0; i < tablicaRozmiar; i++){
        std::cout<<tablica[i]<<" ";
    }
    std::cout<<"\n";
}
    return 0;
}