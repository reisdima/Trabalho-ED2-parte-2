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
        if(registroAux[i] != NULL && userId == registroAux[i]->getUserId() && movieId == registroAux[i]->getMovieId()){
            return true;
        }
        if(aux->ehFolha()){
            return false;
        }

        aux = aux->getFilho(i);
    }
}


void ArvoreB::Inserir(Registro *registro){
    NoB *pt = NULL;
    int posicaoChave = 0;
    bool achou = Buscar(registro, &pt, &posicaoChave);
    cout << "oi" << endl;
    if(!achou){                                                     //Se não achou, inserir o valor na árvore
        if(pt->numeroChaves == 2*d){                                    //Se o numero de chaves no vetor for 2*d precisa fazer cisão
            Cisao(registro, &pt, posicaoChave, NULL);
        }
        else{
            inserirNaoCheio(registro, &pt, posicaoChave);
        }
    }
    else{
        cout << "[WARNING] O registro ja foi inserido!" << endl;
    }
}


void ArvoreB::Cisao(Registro *registro, NoB **pt, int posicaoChave, NoB *outroNo){
    NoB *novoNo = new NoB(d);
    int numeroChaves = (*pt)->numeroChaves;
    Registro **chaves = (*pt)->getRegistros();
    Registro *novasChaves[2*d + 1];
    for(int j = 0; j < numeroChaves; j++){
        novasChaves[j] = chaves[j];
    }
    for(int j = numeroChaves - 1; j>= posicaoChave; j--){
        novasChaves[j+1] = novasChaves[j];
    }
    novasChaves[posicaoChave] = registro;
    Registro **chavesAux = novoNo->getRegistros();
    int k = 0;
    for(int j = d+1; j < 2*d + 1; j++){
        chavesAux[k] = novasChaves[j];
        k++;
    }
    for(int j = 0; j < d; j ++){
        chaves[j] = novasChaves[j];
    }
    (*pt)->numeroChaves = d;
    novoNo->numeroChaves = d;
    NoB** filhosNovoNo = novoNo->getFilhos();
    NoB** filhosPt = (*pt)->getFilhos();

    filhosNovoNo[0] = filhosPt[3];
    filhosNovoNo[1] = filhosPt[4];
    filhosNovoNo[2] = outroNo;
    if(outroNo != NULL){
        novoNo->setFolha(false);
        outroNo->setPai(novoNo);
    }

    NoB *pai = (*pt)->getPai();
    if(pai == NULL){
        NoB *novoPai = new NoB(d);
        novoPai->setFolha(false);
        Registro **chavesPai = novoPai->getRegistros();
        chavesPai[0] = novasChaves[d];
        novoPai->numeroChaves = 1;
        NoB **filhosPai = novoPai->getFilhos();
        filhosPai[0] = (*pt);
        filhosPai[1] = novoNo;
        (*pt)->setPai(novoPai);
        novoNo->setPai(novoPai);
        this->raiz = novoPai;
    }
    else{
        novoNo->setPai(pai);
        int  numChavesPai = pai->numeroChaves;
        Registro **chavesPai = pai->getRegistros();
        int j = 0;
        while(j < numChavesPai && chavesPai[j] < novasChaves[d])
            j++;
        if(numChavesPai < 2*d){
            inserirNaoCheio(novasChaves[d], &pai, j);
            NoB **filhosPai = pai->getFilhos();
            for(int i = numChavesPai; i >= j; i--)
                filhosPai[i+1] = filhosPai[i];
            filhosPai[j+1] = novoNo;
        }
        else{
            Cisao(novasChaves[d], &pai, j, novoNo);
            NoB **filhosPai = pai->getFilhos();
            for(int i = numChavesPai; i >= j; i--)
                filhosPai[i+1] = filhosPai[i];
            filhosPai[j+1] = novoNo;
        }
    }
}


void ArvoreB::inserirNaoCheio(Registro *registro, NoB **pt, int posicaoChave){
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
        Cisao(registro, pt, i, NULL);
    }
    return i;
}
