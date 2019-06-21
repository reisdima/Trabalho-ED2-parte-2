#include "NoVP.h"
#include <iostream>
using namespace std;

NoVP::NoVP(int valor)
{
    this->valor = valor;
    esquerda=direita = pai = NULL;
}

NoVP::~NoVP()
{
    //dtor
}

int NoVP::getUserId(){
   // return this->registro->getMovieId();
}

int NoVP::getMovieId(){
  //  return this->registro->getMovieId();
}
