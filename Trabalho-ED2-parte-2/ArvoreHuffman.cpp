#include "ArvoreHuffman.h"
#include "NoHuffman.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

ArvoreHuffman::ArvoreHuffman(string texto_1)
{
    this->texto = texto_1;
    NoHuffman *raiz = new NoHuffman();
    raiz = nullptr;
    taxaCompressao = 0;
    bytesComprimido = 0;
    codificada = "";
}

ArvoreHuffman::~ArvoreHuffman()
{
    auxDestrutor(this->raiz);
}

void ArvoreHuffman::auxDestrutor(NoHuffman *no)
{
    if(no!= NULL)
    {
        auxDestrutor(no->getNoDir());
        auxDestrutor(no->getNoEsq());
        delete no;
    }
}

void ArvoreHuffman::criaArvoreHuffman()
{
    //faz a contagem das frequencias de cada caractere e armazena em um map
    unordered_map<char, int> freq;
    for (char ch: texto) {
        freq[ch]++;
    }

    //cria uma fila de prioridade para armazenar os n�s da arvore
    priority_queue<NoHuffman*, vector<NoHuffman*>, comp> fp;

    //Cria um n� folha para cada caractere e adiciona a fila de prioridade
    for (auto pair: freq) {
        NoHuffman* no = new NoHuffman(pair.first,pair.second);
        fp.push(no);
    }

    while (fp.size() > 1)
    {
        // Remove os n�s com menor frequencia da fila
        NoHuffman *esq = new NoHuffman();
        esq = fp.top(); fp.pop();
        NoHuffman *dir = new NoHuffman();
        dir = fp.top(); fp.pop();


        // Cria um n� interno cuja frequencia � a soma
        // da frequencia dos dois n�s
        // e coloca esses n�s como filhos,
        // adicionando o novo n� a fila
        int soma = esq->getFreq() + dir->getFreq();
        NoHuffman *no = new NoHuffman('\0', soma, esq, dir);
        fp.push(no);
    }

    //coloca o ultimo n� da fila como raiz
    raiz = fp.top();

}

void ArvoreHuffman::chamaCodificador()
{
    //Codifica cada caractere
    codificador(raiz,"");

    //Codifica a string completa
    for (char ch: texto) {
        codificada += huffmanCode[ch];
    }
    taxaCompressao = codificada.size();
    bytesComprimido = (float)taxaCompressao/8.0;
}

/**
    Fun��o Recursiva que codifica o texto de acordo
    com a arvore ja criada,
*/
void ArvoreHuffman::codificador(NoHuffman* raiz,string str)
{
    if(raiz == nullptr)
    {
        return;
    }
    //cout<<huffmanCode[raiz->getData()];

    // encontra um n� folha
    if (!raiz->getNoEsq() && !raiz->getNoDir())
    {
        huffmanCode[raiz->getData()] = str;
    }
    codificador(raiz->getNoEsq(), str + "0");
    codificador(raiz->getNoDir(), str + "1");
}

void ArvoreHuffman::imprimiCodigoHuffman()
{
    cout<<codificada<<endl;
}
