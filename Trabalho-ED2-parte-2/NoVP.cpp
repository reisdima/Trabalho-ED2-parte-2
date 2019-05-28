#include "NoVP.h"

NoVP::NoVP(Registro *registro)
{
    this->registro = registro;
    cor = 1;
}

NoVP::~NoVP()
{
    //dtor
}


void NoVP::setCor(int cor){
    this->cor = cor;
}


int NoVP::getUserId(){
    return this->registro->getMovieId();
}

int NoVP::getMovieId(){
    return this->registro->getMovieId();
}
