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
    int posicaoChave;
    bool achou = Buscar(registro, &pt, &posicaoChave);
    if(!achou){                                                     //Se não achou, inserir o valor na árvore
        int numeroChaves = pt->numeroChaves;
        if(numeroChaves == 2*d){                                    //Se o numero de chaves no vetor for 2*d
                                                                    //precisa fazer cisão
        }
        else{
            Registro **registros = pt->getRegistros();
            for(int j = numeroChaves - 1; j >= posicaoChave; j--){  //Loop para puxar valores para frente no vetor
                registros[j+1] = registros[j];                       //para inserir o novo valor
            }
            registros[posicaoChave] = registro;
            pt->numeroChaves = pt->numeroChaves + 1;
        }
    }
    else{
        cout << "[WARNING] O registro ja foi inserido!" << endl;
    }
}
