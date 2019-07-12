#include "ArvoreHuffman.h"
#include "NoHuffman.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

ArvoreHuffman::ArvoreHuffman(string texto_1){
    this->texto = texto_1;
    NoHuffman *raiz = new NoHuffman();
    raiz = nullptr;
    taxaCompressao = 0;
    bytesComprimido = 0;
    codificada = "";
}

ArvoreHuffman::~ArvoreHuffman(){
    auxDestrutor(this->raiz);
}

void ArvoreHuffman::auxDestrutor(NoHuffman *no){
    if(no!= NULL){
        auxDestrutor(no->getNoDir());
        auxDestrutor(no->getNoEsq());
        delete no;
    }
}

void ArvoreHuffman::criarArvoreHuffman(){
    unordered_map<char, int> frequencia;
    for (char ch: texto){
        frequencia[ch]++;
    }

    //fila de prioridade para armazenar os nós da arvore
    priority_queue<NoHuffman*, vector<NoHuffman*>, comp> fila;

    //Cria um nó folha para cada caractere e adiciona a fila de prioridade
    for (auto pair: frequencia){
        NoHuffman* no = new NoHuffman(pair.first,pair.second);
        fila.push(no);
    }

    while (fila.size() > 1){
        // Remove os nós com menor frequencia da fila
        NoHuffman *esq = new NoHuffman();
        esq = fila.top(); fila.pop();
        NoHuffman *dir = new NoHuffman();
        dir = fila.top(); fila.pop();

        //Cria no com frequencia igual a soma da frequencia
        //da direita e da esquerda
        int soma = esq->getFrequencia() + dir->getFrequencia();
        NoHuffman *no = new NoHuffman('\0', soma, esq, dir);
        fila.push(no);
    }
    raiz = fila.top();

}

void ArvoreHuffman::chamarCodificador(){
    codificador(raiz, "");
    for (char ch: texto){
        codificada += huffmanCode[ch];
    }
    taxaCompressao = codificada.size();
    bytesComprimido = (float)taxaCompressao/8.0;
}

void ArvoreHuffman::codificador(NoHuffman* raiz,string str){
    if(raiz == nullptr)
        return;
    if (!raiz->getNoEsq() && !raiz->getNoDir()){
        huffmanCode[raiz->getData()] = str;
    }
    codificador(raiz->getNoEsq(), str + "0");
    codificador(raiz->getNoDir(), str + "1");
}

void ArvoreHuffman::imprimirCodigoHuffman(){
    cout<<codificada<<endl;
}

float ArvoreHuffman::getTaxaCompressao(){
    return taxaCompressao = ((float)taxaCompressao/(float)(texto.size()*8));
}

