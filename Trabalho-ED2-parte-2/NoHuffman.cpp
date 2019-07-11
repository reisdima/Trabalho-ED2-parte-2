#include "NoHuffman.h"
#include <stdio.h>
#include <iostream>

using namespace std;

NoHuffman::NoHuffman()
{
    this->freq = 0;
    this->esq = this->dir = NULL;
}

NoHuffman::NoHuffman(char data_1, int freq_1)
{
    this->data = data_1;
    this->freq = freq_1;
    this->esq = this->dir = NULL;
}

NoHuffman::NoHuffman(char data_1, int freq_1, NoHuffman* left, NoHuffman* right)
{
    this->data = data_1;
    this->freq = freq_1;
    this->esq = left;
    this->dir = right;
}

NoHuffman::~NoHuffman(){

}

NoHuffman* NoHuffman::getNoDir()
{
    return this->dir;
}

NoHuffman* NoHuffman::getNoEsq()
{
    return this->esq;
}

void NoHuffman::setNoDir(NoHuffman *novo)
{
    this->dir = novo;
}

void NoHuffman::setNoEsq(NoHuffman *novo)
{
    this->esq = novo;
}

int NoHuffman::getFreq()
{
    return this->freq;
}

char NoHuffman::getData()
{
    return this->data;
}

void NoHuffman::setFreq(int novaF)
{
    this->freq = novaF;
}

void NoHuffman::setData(char novaD)
{
    this->data = novaD;
}
