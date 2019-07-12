#include <iostream>
#include "ArvoreVP.h"
#include "NoVP.h"
#include <bits/stdc++.h>
using namespace std;

ArvoreVP::ArvoreVP()
{
    this->numeroComparacao = 0;
    this->numeroComparacaoBusca = 0;
    this->numeroCopias = 0;
    this->raiz = NULL;
}

ArvoreVP::~ArvoreVP()
{
    //dtor
}


void ArvoreVP::auxEmOrdem(NoVP *raiz){
    int userId1 = raiz->getUserId();
    int movieId1 = raiz->getMovieId();
    numeroComparacao++;
    numeroCopias++;
    if(raiz==NULL){
        return;
    }
    auxEmOrdem(raiz->esquerda);
    auxEmOrdem(raiz->direita);
}

NoVP* ArvoreVP::AVPInserir(NoVP *noRaiz, NoVP *pt){
    numeroComparacao++;
    if(noRaiz==NULL){
        return pt;
    }
    int userId1 = noRaiz->getUserId();
    int movieId1 = noRaiz->getMovieId();
    int userId2 = pt->getUserId();
    int movieId2 = pt->getMovieId();
    numeroCopias += 4;
    numeroComparacao += 3;
    if(userId2 < userId1 || (userId2 == userId1 && movieId2 < movieId1)){
        numeroCopias +=2 ;
        noRaiz->esquerda = AVPInserir(noRaiz->esquerda, pt);
        noRaiz->esquerda->pai = noRaiz;
    }
    else if(userId2 > userId1 || (userId2 == userId1 && movieId2 > movieId1)){
        numeroComparacao += 3;
        numeroCopias += 2;
        noRaiz->direita = AVPInserir(noRaiz->direita, pt);
        noRaiz->direita->pai = noRaiz;
    }
    return noRaiz;
}

void ArvoreVP::auxNivelOrdem(NoVP *raiz){
    numeroComparacao++;
    if(raiz==NULL){
        return;
    }
        std::queue<NoVP *> q;
        q.push(raiz);
        numeroComparacao++;
        while(!q.empty()){
            NoVP *temp = q.front();
            cout<<temp->valor<<" ";
            q.pop();
            numeroComparacao++;
            if(temp->esquerda != NULL){
                q.push(temp->esquerda);
            }
            numeroComparacao++;
            if(temp->direita != NULL){
                q.push(temp->direita);
            }
            numeroComparacao++;
        }
}

void ArvoreVP::rotacionaEsquerda(NoVP *&raiz,NoVP *&pt ){
    NoVP *ptDireita = pt->direita;
    pt->direita = ptDireita->esquerda;
    numeroCopias += 2;
    numeroComparacao++;
    if(pt->direita != NULL){
        pt->direita->pai = pt;
        numeroCopias++;
    }
    ptDireita->pai = pt->pai;
    numeroCopias++;
    numeroComparacao++;
    if(pt->pai == NULL){
        raiz = ptDireita;
        numeroCopias++;
    }
    else if(pt == pt->pai->esquerda){
        numeroComparacao++;
        numeroCopias++;
        pt->pai->esquerda = ptDireita;
    }
    else{
        pt->pai->direita=ptDireita;
        numeroCopias++;
    }
    ptDireita->esquerda = pt;
    pt->pai = ptDireita;
    numeroCopias += 2;
}

void ArvoreVP::rotacionaDireita(NoVP *&noRaiz,NoVP *&pt ){
    NoVP *ptEsquerda = pt->esquerda;
    pt->esquerda = ptEsquerda->direita;
    numeroCopias += 2;
    numeroComparacao++;
    if(pt->esquerda != NULL){
        pt->esquerda->pai = pt;
        numeroCopias++;
    }

    ptEsquerda->pai = pt->pai;
    numeroComparacao++;
    numeroCopias++;
    if(pt->pai == NULL){
        noRaiz = ptEsquerda;
        numeroCopias++;
    }
    else if(pt == pt->pai->esquerda){
        numeroComparacao++;
        numeroCopias++;
        pt->pai->esquerda = ptEsquerda;
    }
    else{
        pt->pai->direita = ptEsquerda;
        numeroCopias++;
    }
    ptEsquerda->direita = pt;
    pt->pai = ptEsquerda;
    numeroCopias += 2;
}

void ArvoreVP::correcao(NoVP *raiz, NoVP *ponteiro){
    NoVP *paiPt = NULL;
    NoVP *avoPt = NULL;
    numeroComparacao += 3;
    while((ponteiro != raiz) && ponteiro->cor != false && (ponteiro->pai->cor == true)){
        paiPt = ponteiro->pai;
        avoPt = ponteiro->pai->pai;
        numeroCopias += 2;
        numeroComparacao++;
        if(paiPt == avoPt->esquerda){
            NoVP *tioPt = avoPt->direita;
            numeroCopias++;
            numeroComparacao += 2;
            if(tioPt != NULL && tioPt->cor == true){
                avoPt->cor=true;
                paiPt->cor=false;
                tioPt->cor=false;
                ponteiro = avoPt;
                numeroCopias++;
            }
            else{
                numeroComparacao++;
                if(ponteiro == paiPt->direita){
                    rotacionaEsquerda(raiz, paiPt);
                    ponteiro = paiPt;
                    paiPt = ponteiro->pai;
                    numeroCopias += 2;
                }

                rotacionaDireita(raiz, avoPt);
                swap(paiPt->cor, avoPt->cor);;
                ponteiro = paiPt;
                numeroCopias += 2;
            }
        }
        else{
            NoVP *tioPt = avoPt->esquerda;
            numeroCopias++;
            numeroComparacao++;
            if((tioPt != NULL) && (tioPt->cor == true)){
                avoPt->cor = true;
                paiPt->cor = false;
                tioPt->cor = false;
                ponteiro = avoPt;
                numeroCopias++;
            }
            else{
                numeroComparacao++;
                if(ponteiro == paiPt->esquerda){
                    rotacionaDireita(raiz,paiPt);
                    ponteiro=paiPt;
                    paiPt=ponteiro->pai;
                    numeroCopias += 2;
                }
                rotacionaEsquerda(raiz,avoPt);
                swap(paiPt->cor, avoPt->cor);
                ponteiro=paiPt;
                numeroCopias += 2;
            }
         }
    }
    raiz->cor=false;
}

void ArvoreVP::Inserir(Registro *registro){
    NoVP *pt = new NoVP(registro);
    numeroCopias++;
    raiz = AVPInserir(raiz, pt);
    correcao(raiz, pt);
}

void ArvoreVP::emOrdem(){
    auxEmOrdem(raiz);
}

void ArvoreVP::nivelOrdem(){
    auxNivelOrdem(raiz);
}



unsigned long int ArvoreVP::getNumeroComparacao(){
    return this->numeroComparacao;
}

unsigned long int ArvoreVP::getNumeroCopias(){
    return this->numeroCopias;
}


unsigned long int ArvoreVP::getNumeroComparacaoBusca(){
    return this->numeroComparacaoBusca;
}

bool ArvoreVP::Buscar(Registro *registro){
    numeroComparacaoBusca++;
    if(raiz == NULL)
        return false;
    NoVP *aux = raiz;
    int userId1 = registro->getUserId();
    int movieId1 = registro->getMovieId();

    numeroComparacaoBusca++;
    while(aux != NULL){
        int userId2 = aux->getUserId();
        int movieId2 = aux->getMovieId();
        numeroComparacaoBusca++;
        if(userId1 < userId2 || (userId1 == userId2 && movieId1 < movieId2))
            aux = aux->esquerda;
        else if(userId1 > userId2 || (userId1 == userId2 && movieId1 > movieId2))
            aux = aux->direita;
        else
            return true;
        numeroComparacaoBusca += 2;
    }
    return false;
}
