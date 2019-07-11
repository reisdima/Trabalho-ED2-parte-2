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
    void Parte1();
    void Parte2();
    void escritaSaidaAVP(int bytes, fstream myfile);
};

#endif // MENU_H
