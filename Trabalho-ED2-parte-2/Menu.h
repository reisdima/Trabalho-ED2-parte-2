#ifndef MENU_H
#define MENU_H
#include "ArvoreVP.h"

using namespace std;

class Menu
{
public:
    Menu();
    ~Menu();
    void ExibirMenu();
private:
    int *vetorN;
    int tamanhoN;
    void Parte1_ArvoreB();
    void Parte1_ArvoreVP();
    void Parte1();
    void Parte2();
    void leituraN();
};

#endif // MENU_H
