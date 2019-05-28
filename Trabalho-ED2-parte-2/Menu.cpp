#include <iostream>
#include "Menu.h"
using namespace std;

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}


void Menu::ExibirMenu(){
    int escolha = -1;
    cout << "Insira o que deseja fazer: " << endl;
    while(escolha != 0){
        cout << endl << "1. Parte 1" << endl;
        cout << "2. Parte 2" << endl;
        cout << "0. Encerrar o programa" << endl << endl;
        cin >> escolha;
        switch(escolha){
        case 1:
            Parte1();
            escolha = 0;
            break;
        case 2:
            Parte2();
            escolha = 0;
            break;
        case 0:
            break;
        default:
            cout << endl <<  "Por favor insira um valor correto" << endl;
        }
    }
}


void Menu::Parte1(){
    cout << "Voce entrou na aprte 1" << endl;
}
void Menu::Parte2(){
    cout << "Parte 2" << endl;
}
