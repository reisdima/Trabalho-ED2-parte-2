#ifndef NOVP_H
#define NOVP_H
#include "Registro.h"
using namespace std;


enum Cor{VERMELHO,PRETO};
class NoVP
{
public:
    NoVP(int valor);
    NoVP(Registro *registro);
    ~NoVP();
    bool cor; //0 = preto; 1 = vermelho
    int valor;
    Registro *registro;
    NoVP *esquerda, *direita, *pai;


    int getMovieId();
    int getUserId();

private:

};

#endif // NOVP_H
