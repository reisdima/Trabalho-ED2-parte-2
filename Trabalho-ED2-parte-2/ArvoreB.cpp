#include "ArvoreB.h"
#include <iostream>
using namespace std;

ArvoreB::ArvoreB(int d)
{
    this->numeroComparacao = 0;
    this->numeroComparacaoBusca = 0;
    this->numeroCopias = 0;
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
    numeroComparacaoBusca++;
    while(aux != NULL){
        int numeroChaves = aux->numeroChaves;
        Registro **registroAux = aux->getRegistros();
        int i = 0;
        numeroComparacaoBusca++;
        while(i < numeroChaves && (registroAux[i]->getUserId() < userId ||
                                   (registroAux[i]->getUserId() == userId && registroAux[i]->getMovieId() < movieId))){
            i++;
            numeroComparacaoBusca += 3;
        }
        numeroComparacaoBusca++;
        if(i < numeroChaves && registroAux[i] != NULL && userId == registroAux[i]->getUserId() && movieId == registroAux[i]->getMovieId())
            return true;
        numeroComparacaoBusca++;
        if(aux->ehFolha())
            return false;
        aux = aux->getFilho(i);
        numeroComparacaoBusca++;
    }
}

bool ArvoreB::Buscar(Registro *registro, NoB **pt, int *posicaoChave){
    NoB *aux = raiz;
    int userId = registro->getUserId();
    int movieId = registro->getMovieId();
    numeroComparacao++;
    while(aux != NULL){
        (*pt) = aux;
        int numeroChaves = aux->numeroChaves;
        Registro **registroAux = aux->getRegistros();
        int i = 0;
        numeroComparacao += 3;
        while(i < numeroChaves && (registroAux[i]->getUserId() < userId ||
                                   (registroAux[i]->getUserId() == userId && registroAux[i]->getMovieId() < movieId))){
            i++;
            numeroComparacao += 3;
        }
        *posicaoChave = i;
        numeroComparacao += 4;
        if(i < numeroChaves && registroAux[i] != NULL && userId == registroAux[i]->getUserId() && movieId == registroAux[i]->getMovieId()){
            return true;
        }
        if(aux->ehFolha()){
            return false;
        }

        aux = aux->getFilho(i);
        numeroComparacao++;
    }
}


void ArvoreB::Inserir(Registro *registro){
    NoB *pt = NULL;
    int posicaoChave = 0;
    bool achou = Buscar(registro, &pt, &posicaoChave);
    if(!achou){                                                         //Se não achou, inserir o valor na árvore
        numeroComparacao++;
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
    numeroComparacao++;
    for(int j = 0; j < numeroChaves; j++){
        novasChaves[j] = chaves[j];
        numeroComparacao++;
        numeroCopias++;
    }
    numeroComparacao++;
    for(int j = numeroChaves - 1; j>= posicaoChave; j--){
        novasChaves[j+1] = novasChaves[j];
        numeroComparacao++;
        numeroCopias++;
    }
    novasChaves[posicaoChave] = registro;
    Registro **chavesAux = novoNo->getRegistros();
    int k = 0;
    numeroComparacao++;
    for(int j = d+1; j < 2*d + 1; j++){
        chavesAux[k] = novasChaves[j];
        k++;
        numeroComparacao++;
        numeroCopias++;
    }
    numeroComparacao++;
    for(int j = 0; j < d; j ++){
        chaves[j] = novasChaves[j];
        numeroComparacao++;
        numeroCopias++;
    }
    (*pt)->numeroChaves = d;
    novoNo->numeroChaves = d;
    NoB** filhosNovoNo = novoNo->getFilhos();
    NoB** filhosPt = (*pt)->getFilhos();
    k = numeroChaves;
    numeroComparacao++;
    for(int i = 0; i < d; i++){
        filhosNovoNo[i] = filhosPt[k];
        k--;
        numeroCopias++;
        numeroComparacao++;
    }
    filhosNovoNo[d] = outroNo;
    numeroCopias++;
    numeroComparacao++;
    if(outroNo != NULL){
        novoNo->setFolha(false);
        outroNo->setPai(novoNo);
    }

    NoB *pai = (*pt)->getPai();
    numeroCopias++;
    numeroComparacao++;
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
        numeroCopias += 3;
    }
    else{
        novoNo->setPai(pai);
        int  numChavesPai = pai->numeroChaves;
        Registro **chavesPai = pai->getRegistros();
        int j = 0;
        numeroComparacao += 2;
        numeroCopias += 2;
        while(j < numChavesPai && chavesPai[j] < novasChaves[d]){
            j++;
            numeroComparacao += 2;
        }
        numeroComparacao++;
        if(numChavesPai < 2*d){
            inserirNaoCheio(novasChaves[d], &pai, j);
            NoB **filhosPai = pai->getFilhos();
            numeroComparacao++;
            for(int i = numChavesPai; i >= j; i--){
                filhosPai[i+1] = filhosPai[i];
                numeroCopias++;
                numeroComparacao++;
            }
            filhosPai[j+1] = novoNo;
            numeroCopias++;
        }
        else{
            Cisao(novasChaves[d], &pai, j, novoNo);
            NoB **filhosPai = pai->getFilhos();
            numeroComparacao++;
            for(int i = numChavesPai; i >= j; i--){
                numeroCopias++;
                filhosPai[i+1] = filhosPai[i];
                numeroComparacao++;
            }
            filhosPai[j+1] = novoNo;
            numeroCopias++;
        }
    }
}


void ArvoreB::inserirNaoCheio(Registro *registro, NoB **pt, int posicaoChave){
    int numeroChaves = (*pt)->numeroChaves;
    Registro **registros = (*pt)->getRegistros();
    numeroComparacao++;
    for(int j = numeroChaves - 1; j >= posicaoChave; j--){  //Loop para puxar valores para frente no vetor
        registros[j+1] = registros[j];                       //para inserir o novo valor
        numeroCopias++;
        numeroComparacao++;
    }
    registros[posicaoChave] = registro;
    numeroCopias++;
    (*pt)->numeroChaves = (*pt)->numeroChaves + 1;
}


unsigned long int ArvoreB::getNumeroComparacao(){
    return this->numeroComparacao;
}

unsigned long int ArvoreB::getNumeroCopias(){
    return this->numeroCopias;
}


unsigned long int ArvoreB::getNumeroComparacaoBusca(){
    return this->numeroComparacaoBusca;
}

