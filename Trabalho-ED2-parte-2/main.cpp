#include <iostream>
#include <cstdlib>
#include "Menu.h"
#include "ArvoreVP.h"
#include "NoVP.h"
using namespace std;
/**
 CODIGO DE HUFFMAN INICIO
*/

struct No{
    char dado;
    int freq;
    No *esq, *dir;
};

No* getNo(char dado, int freq, No* esquerda, No* direita){
    No* no= new No();
    no->dado=dado;
    no->freq=freq;
    no->esq=esquerda;
    no->dir=direita;
    return no;
}

struct compara{
    bool operator()(No* esq, No* dir){
        return esq->freq > dir->freq;
    }
};

void encode(No* raiz, string texto, unordered_map<char, string> &Huffman){
    if(raiz==nullptr){
        return;
    }
    if(!raiz->esq&&!raiz->dir){
        Huffman[raiz->dado]=texto;
    }
    encode(raiz->esq, texto+"0",Huffman);
    encode(raiz->dir, texto+"1",Huffman);
}

void decode(No* raiz, int &indice, string texto){
    if(raiz==nullptr){
        return;
    }
    if(!raiz->esq&&!raiz->dir){
        cout<<raiz->dado;
        return;
    }
    indice++;
    if(texto[indice]=='0'){
        decode(raiz->esq, indice, texto);
    }
    else{
        decode(raiz->dir, indice, texto);
    }
}

void montaHuffman(string texto){
    unordered_map<char, int>freq;
    for(char dado:texto){
        freq[dado]++;
    }
    priority_queue<No*,vector<No*>, compara> fp;

    for(auto pair:freq){
        fp.push(getNo(pair.first, pair.second,nullptr,nullptr));
    }

    while(fp.size()!=1){
        No *esquerda=fp.top(); fp.pop();
        No *direita = fp.top(); fp.pop();
        int soma = esquerda->freq + direita->freq;
        fp.push(getNo('\0',soma,esquerda,direita));
    }
    No* raiz=fp.top();
    unordered_map<char, string> Huffman;
    encode(raiz,"",Huffman);
    cout<<"Codigo Huffman: \n"<<'\n';
    for(auto pair: Huffman){
        cout<<pair.first<< " "<<pair.second<<'\n';
    }
    cout<<"\nO texto original era: \n"<<texto<<'\n';

    string str="";
    for(char ch: texto){
        str+=Huffman[ch];
    }
    cout<<"A string codificada e: "<<endl<<str;
}
/**
 CODIGO DE HUFFMAN FIM
*/



int main()
{
    Menu menu;
    menu.ExibirMenu();

/**
    TESTE ARVORE VERMELHO-PRETO
    ArvoreVP arvoreVP;

    arvoreVP.Inserir(7);
    arvoreVP.Inserir(6);
    arvoreVP.Inserir(5);
    arvoreVP.Inserir(4);
    arvoreVP.Inserir(3);
    arvoreVP.Inserir(2);
    arvoreVP.Inserir(1);

    cout << "Inoder Traversal of Created Tree\n";
    arvoreVP.emOrdem();

    cout << "\n\nLevel Order Traversal of Created Tree\n";
    arvoreVP.nivelOrdem();

 */


/**
    TESTE CODIFICAÇĂO HUFFMAN
    //string texto="Huffman coding is a data compression algorithm.";
    //montaHuffman(texto);
 */

    return 0;
}
