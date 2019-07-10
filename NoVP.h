#ifndef NOVP_H
#define NOVP_H
#include "Registro.h"
using namespace std;


enum Cor{VERMELHO,PRETO};
class NoVP
{
public:
    bool cor; //0 = preto; 1 = vermelho
    int valor;
    NoVP *esquerda, *direita, *pai;
    NoVP(int valor);
    ~NoVP();

    int getMovieId();
    int getUserId();

private:

};

#endif // NOVP_H
