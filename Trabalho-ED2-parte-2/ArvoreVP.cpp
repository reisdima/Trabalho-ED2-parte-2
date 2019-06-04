#include <iostream>
#include "ArvoreVP.h"

using namespace std;

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



}

