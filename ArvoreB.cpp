#include "ArvoreB.h"
#include <iostream>
using namespace std;

ArvoreB::ArvoreB(int d)
{
    this->d = d;
    raiz = new NoB(this->d);
}

ArvoreB::~ArvoreB()
{
    //dtor
}


bool ArvoreB::Buscar(Registro *registro){
    NoB *aux = raiz;
    int userId = registro->getUserId();
    int movieId = registro->getMovieId();
    while(aux != NULL){
        int numeroChaves = aux->numeroChaves;
        Registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getUserId() < userId ||
                                   (registroAux[i]->getUserId() == userId && registroAux[i]->getMovieId() < movieId))){
            i++;
        }
        if(userId == registroAux[i]->getUserId() && movieId == registroAux[i]->getMovieId())
            return true;
        if(aux->ehFolha())
            return false;
        aux = aux->getFilho(i);
    }
}

bool ArvoreB::Buscar(Registro *registro, NoB **pt, int *posicaoChave){
    NoB *aux = raiz;
    int userId = registro->getUserId();
    int movieId = registro->getMovieId();
    while(aux != NULL){
        (*pt) = aux;
        int numeroChaves = aux->numeroChaves;
        Registro **registroAux = aux->getRegistros();
        int i = 0;
        while(i < numeroChaves && (registroAux[i]->getUserId() < userId ||
                                   (registroAux[i]->getUserId() == userId && registroAux[i]->getMovieId() < movieId))){
            i++;
        }
        *posicaoChave = i;
        if(userId == registroAux[i]->getUserId() && movieId == registroAux[i]->getMovieId())
            return true;
        if(aux->ehFolha())
            return false;
        aux = aux->getFilho(i);
    }
}


void ArvoreB::Inserir(Registro *registro){
    NoB *pt = NULL;
    int posicaoChave = 0;
    bool achou = Buscar(registro, &pt, &posicaoChave);
    if(!achou){                                                     //Se não achou, inserir o valor na árvore
        if(pt->numeroChaves == 2*d){                                    //Se o numero de chaves no vetor for 2*d precisa fazer cisão
            Cisao(registro, &pt, posicaoChave);
            /*Registro **registros = pt->getRegistros();
            Registro **auxRegistros = new Registro*[2*d + 1];
            NoB *pai = pt->getPai();
            if(pai == NULL){
                int i = posicaoChave;
                for(int j = 0; j < numeroChaves; j++){
                    auxRegistros[j] = registros[j];
                }
                for(int j = numeroChaves - 1; j>= i; j--){
                    auxRegistros[j+1] = registros[j];
                }
                auxRegistros[posicaoChave] = registro;
                NoB *A = new NoB(d);
                NoB *B = new NoB(d);
                Registro **chavesAux = A->getRegistros();
                for(int j = 0; j < d; j++){
                    chavesAux[j] = auxRegistros[j];
                }
                chavesAux = B->getRegistros();
                int k = 0;
                for(int j = d+1; j < 2*d+1; j++){
                    chavesAux[k] = auxRegistros[j];
                    k++;
                }
                A->numeroChaves = 2;
                B->numeroChaves = 2;

                /*
                chaves[0] = chaves[d];
                pt->numeroChaves = numeroChaves++;
                A->setPai(pt);
                B->setPai(pt);
                NoB **filhos = pt->getFilho();
            }*/
        }
        else{
            inserirNaoNulo(registro, &pt, posicaoChave);
        }
    }
    else{
        cout << "[WARNING] O registro ja foi inserido!" << endl;
    }
}


void ArvoreB::Cisao(Registro *registro, NoB **pt, int posicaoChave){
    Registro **registros = (*pt)->getRegistros();
    Registro **auxRegistros = new Registro*[2*d + 1];
    NoB *pai = (*pt)->getPai();
    int numeroChaves = (*pt)->numeroChaves;
    if(pai == NULL){
        for(int j = 0; j < numeroChaves; j++){
            auxRegistros[j] = registros[j];
        }
        for(int j = numeroChaves - 1; j >= posicaoChave; j--){
            auxRegistros[j+1] = registros[j];
        }
        auxRegistros[posicaoChave] = registro;
        NoB *esq = new NoB(d);
        NoB *dir = new NoB(d);
        Registro **chavesAux = esq->getRegistros();
        for(int j = 0; j < d; j++){
            chavesAux[j] = auxRegistros[j];
        }
        chavesAux = dir->getRegistros();
        int k = 0;
        for(int j = d+1; j < 2*d+1; j++){
            chavesAux[k] = auxRegistros[j];
            k++;
        }
        esq->numeroChaves = 2;
        dir->numeroChaves = 2;
        esq->setPai(*pt);
        dir->setPai(*pt);
        registros[0] = auxRegistros[(2*d + 1) / 2];
        (*pt)->numeroChaves = 1;
        (*pt)->setFilho(esq, 0);
        (*pt)->setFilho(dir, 1);
        (*pt)->setFolha(false);
    }
    else{
        for(int j = 0; j < numeroChaves; j++){
            auxRegistros[j] = registros[j];
        }
        for(int j = numeroChaves - 1; j >= posicaoChave; j--){
            auxRegistros[j+1] = registros[j];
        }
        auxRegistros[posicaoChave] = registro;
        NoB *esq = new NoB(d);
        NoB *dir = new NoB(d);
        Registro **chavesAux = esq->getRegistros();
        for(int j = 0; j < d; j++){
            chavesAux[j] = auxRegistros[j];
        }
        chavesAux = dir->getRegistros();
        int k = 0;
        for(int j = d+1; j < 2*d+1; j++){
            chavesAux[k] = auxRegistros[j];
            k++;
        }
        esq->numeroChaves = 2;
        dir->numeroChaves = 2;
        esq->setPai(*pt);
        dir->setPai(*pt);
        int posicaoA = Inserir(registro, &pai);
        NoB **filhos = (*pt)->getFilhos();
        filhos[posicaoA] = esq;
        filhos[posicaoA + 1] = dir;
    }
}


void ArvoreB::inserirNaoNulo(Registro *registro, NoB **pt, int posicaoChave){
    int numeroChaves = (*pt)->numeroChaves;
    Registro **registros = (*pt)->getRegistros();
    for(int j = numeroChaves - 1; j >= posicaoChave; j--){  //Loop para puxar valores para frente no vetor
        registros[j+1] = registros[j];                       //para inserir o novo valor
    }
    registros[posicaoChave] = registro;
    (*pt)->numeroChaves = (*pt)->numeroChaves + 1;
}


int ArvoreB::Inserir(Registro *registro, NoB **pt){
    int numeroChaves = (*pt)->numeroChaves;
    Registro **registros = (*pt)->getRegistros();
    int userId = registro->getUserId();
    int movieId = registro->getMovieId();
    int i = 0;
    while(i < numeroChaves && (registros[i]->getUserId() < userId ||
                                   (registros[i]->getUserId() == userId && registros[i]->getMovieId() < movieId))){
            i++;
    }
    if(numeroChaves < 2*d){
        for(int j = numeroChaves - 1; j >= i; j--){  //Loop para puxar valores para frente no vetor
            registros[j+1] = registros[j];                       //para inserir o novo valor
        }
        registros[i] = registro;
        (*pt)->numeroChaves = (*pt)->numeroChaves + 1;
    }
    else{
        Cisao(registro, pt, i);
    }
    return i;
}
