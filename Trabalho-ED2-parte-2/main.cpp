#include <iostream>
#include <cstdlib>
#include "Menu.h"
#include "ArvoreVP.h"
#include "NoVP.h"
using namespace std;
#define ALTMAX 100


/**
 CODIGO DE HUFFMAN INICIO
*/
//Nó da arvore Huffman
struct MinHeapNo{
    char dado;
    unsigned freq;
    struct MinHeapNo *esq, *dir;
};

// "grupo" de nós da árvore Huffman
struct MinHeap{
    unsigned tam;
    unsigned capacidade;
    struct MinHeapNo** vetor;
};

//Aloca um novo nó da arv. Huffman dado o caractere e a sua frequencia
struct MinHeapNo* newNo(char dado, unsigned freq){
    struct MinHeapNo* temp=(struct MinHeapNo*)malloc(sizeof(struct MinHeapNo));
    temp->esq=temp->dir=NULL;
    temp->dado=dado;
    temp->freq=freq;
    return temp;
};

//Cria uma minHeap com a capacidade dada
struct MinHeap* criaMinHeap(unsigned capacidade){
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    //tamanho atual é zero
    minHeap->tam=0;
    minHeap->capacidade=capacidade;
    minHeap->vetor=(struct MinHeapNo**)malloc(minHeap->capacidade*sizeof(struct MinHeapNo*));
    return minHeap;
};

//Troca dois nós min heap
void trocaMinHeapNo(struct MinHeapNo** a, struct MinHeapNo** b){
    struct MinHeapNo* t=*a;
    *a=*b;
    *b=t;
}

//minHeapify padrăo
void minHeapify(struct MinHeap* minHeap, int idx){
    int menor=idx;
    int esquerda = 2*idx+1;
    int direita=2*idx+2;
    if(esquerda<minHeap->tam&&minHeap->vetor[esquerda]->freq<minHeap->vetor[menor]->freq){
        menor=esquerda;
    }
    if(direita<minHeap->tam&&minHeap->vetor[direita]->freq<minHeap->vetor[menor]->freq){
        menor=direita;
    }
    if(menor!=idx){
        trocaMinHeapNo(&minHeap->vetor[menor],&minHeap->vetor[idx]);
        minHeapify(minHeap,menor);
    }
}

//Verifica se o tamanho da heap é 1 ou năo
int tamUm(struct MinHeap* minHeap){
    return (minHeap->tam==1);
}

//Recebe o menor nó (em valor)
struct MinHeapNo* recebeMin(struct MinHeap* minHeap){
    struct MinHeapNo* temp = minHeap->vetor[0];
    minHeap->vetor[0]=minHeap->vetor[minHeap->tam-1];
    --minHeap->tam;
    minHeapify(minHeap, 0);
    return temp;
};

//Insere um novo nó na MinHeap
void insereMinHeap(struct MinHeap* minHeap, struct MinHeapNo* minHeapNo){
    ++minHeap->tam;
    int i = minHeap->tam -1;
    while(i&&minHeapNo->freq<minHeap->vetor[(i-1)/2]->freq){
        minHeap->vetor[i]=minHeap->vetor[(i-1)/2];
        i=(i-1)/2;
    }
    minHeap->vetor[i]=minHeapNo;
}

//Monta a min heap
void montaMinHeap(struct MinHeap* minHeap){
    int n=minHeap->tam-1;
    for(int i=(n-1)/2;i>=0;i--){
        minHeapify(minHeap, i);
    }
}

//Printa o vetor
void printVet(int vetor[], int n){
    for(int i=0; i<n;i++){
        cout<<vetor[i];
    }
    cout<<endl;
}

//Verifica se o nó é folha
int eFolha(struct MinHeapNo* raiz){
    return !(raiz->esq)&& !(raiz->dir);
}

//Cria uma min heap com capacidade=tam e insere todos os dados na min heap.
//O tamanho inicial da min heap é = a capacidade;
struct MinHeap* criaEMontaMinHeap(char dado[], int freq[], int tamanho){
    struct MinHeap* minHeap=criaMinHeap(tamanho);
    for(int i=0;i<tamanho;i++){
        minHeap->vetor[i]=newNo(dado[i],freq[i]);
    }
    minHeap->tam=tamanho;
    montaMinHeap(minHeap);
    return minHeap;
};

//Estrutura principal que monta HUFFMAN
struct MinHeapNo* montaHuffman(char dado[], int freq[], int tamanho){
    struct MinHeapNo *esquerda, *direita, *topo;
    //1- Cria min heap com capacidade=tam;
    struct MinHeap *minHeap=criaEMontaMinHeap(dado,freq,tamanho);
    while(!tamUm(minHeap)){
        //2-Pega as duas menores frequencias
        esquerda=recebeMin(minHeap);
        direita=recebeMin(minHeap);
        //3-cria um novo no com freq=freq dos dois nos
        topo=newNo('S', esquerda->freq+direita->freq);
        topo->esq=esquerda;
        topo->dir=direita;
        insereMinHeap(minHeap,topo);
    }
    //4- o no que sobrou é a raiz
    return recebeMin(minHeap);
};

//Printa Huffman desde a raiz
void printHuffman(struct MinHeapNo* raiz, int vet[], int topo){
    if(raiz->esq){
        vet[topo]=0;
        printHuffman(raiz->esq,vet,topo+1);
    }
    if(raiz->dir){
        vet[topo]=1;
        printHuffman(raiz->dir,vet,topo+1);
    }
    if(eFolha(raiz)){
        cout<<raiz->dado<<": ";
        printVet(vet,topo);
    }
}

void Huffman(char dado[], int freq[], int tam){
    struct MinHeapNo* raiz=montaHuffman(dado,freq,tam);
    int vet[ALTMAX], topo=0;
    printHuffman(raiz,vet,topo);
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
