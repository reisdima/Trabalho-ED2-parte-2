#include <iostream>
#include "ArvoreVP.h"

ArvoreVP::ArvoreVP()
{
    raiz = NULL;
}

ArvoreVP::~ArvoreVP()
{
    //dtor
}


void ArvoreVP::Inserir(Registro *registro){
    NoVP *novo = new NoVP(registro);

    NoVP *aux = raiz;

}

