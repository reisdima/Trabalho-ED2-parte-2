#ifndef ARVOREB_H
#define ARVOREB_H
#include "NoB.h"
#include "Registro.h"

class ArvoreB
{
public:
    ArvoreB(int d);
    ~ArvoreB();

    //Fun��es
    void Inserir(Registro *registro);
    bool Buscar(Registro *registro);
    bool Buscar(Registro *registro, NoB **pt, int *posicaoChave);

private:
    NoB *raiz;
    int d;


};

#endif // ARVOREB_H
