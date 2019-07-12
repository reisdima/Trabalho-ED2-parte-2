#include "NoHuffman.h"
#include <stdio.h>
#include <iostream>

using namespace std;

NoHuffman::NoHuffman(){
    this->frequencia = 0;
    this->esq = NULL;
    this->dir = NULL;
}

NoHuffman::NoHuffman(char data, int frequencia){
    this->data = data;
    this->frequencia = frequencia;
    this->esq = NULL;
    this->dir = NULL;
}

NoHuffman::NoHuffman(char data, int frequencia, NoHuffman* left, NoHuffman* right){
    this->data = data;
    this->frequencia = frequencia;
    this->esq = left;
    this->dir = right;
}

NoHuffman::~NoHuffman(){

}

NoHuffman* NoHuffman::getNoDir(){
    return this->dir;
}

NoHuffman* NoHuffman::getNoEsq(){
    return this->esq;
}

void NoHuffman::setNoDir(NoHuffman *no){
    this->dir = no;
}

void NoHuffman::setNoEsq(NoHuffman *no){
    this->esq = no;
}

int NoHuffman::getFrequencia(){
    return this->frequencia;
}

char NoHuffman::getData(){
    return this->data;
}

void NoHuffman::setFrequencia(int frequencia){
    this->frequencia = frequencia;
}

void NoHuffman::setData(char novaD){
    this->data = novaD;
}
