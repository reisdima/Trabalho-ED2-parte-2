#include "NoB.h"
#include <iostream>

NoB::NoB(int d)
{
    this->d = d;
    registros = new Registro*[2*d];
    filhos = new NoB*[2*d + 1];
    for(int i = 0; i < 2*d; i++){
        filhos[i] = NULL;
        registros[i] = NULL;
    }
    filhos[2*d] = NULL;
    this->folha = true;
    this->pai = NULL;
    numeroChaves = 0;
}

NoB::~NoB()
{
    //dtor
}


void NoB::setFilho(NoB *no, int i){
    filhos[i] = no;
}

void NoB::setFolha(bool ehFolha){
    this->folha = ehFolha;
}

void NoB::setPai(NoB *no){
    this->pai = no;
}

NoB* NoB::getPai(){
    return this->pai;
}

Registro** NoB::getRegistros(){
    return this->registros;
}

bool NoB::ehFolha(){
    return this->folha;
}

NoB* NoB::getFilho(int i){
    return this->filhos[i];
}

NoB** NoB::getFilhos(){
    return filhos;
}
