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

//A funcao ”AVPInserir”encontra a melhor posicao a se
//inserir o Registro. Ao encontrar a melhor posicao se retorna
//a funcao ”Inserir”que entao chama a funcao ”Correcao”.
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

//A func˜ao ”Correcao”ira verificar se a Arvore Vermelho-
//Preto formada esta seguindo aos requisitos adicionais de balanceamento
void ArvoreVP::correcao(NoVP *raiz, NoVP *ponteiro){
    NoVP *paiPt = NULL;
    NoVP *avoPt = NULL;
    numeroComparacao += 3;
    while((ponteiro != raiz) && ponteiro->cor != false && (ponteiro->pai->cor == true)){
        paiPt = ponteiro->pai;
        avoPt = ponteiro->pai->pai;
        numeroCopias += 2;
        numeroComparacao++;
        //Caso 1 pai de pt é filho a esquerda do avo de pt
        if(paiPt == avoPt->esquerda){
            NoVP *tioPt = avoPt->direita;
            numeroCopias++;
            numeroComparacao += 2;
            //Caso 1.1 O Tio do pt tambem é vermelho
            if(tioPt != NULL && tioPt->cor == true){
                avoPt->cor=true;
                paiPt->cor=false;
                tioPt->cor=false;
                ponteiro = avoPt;
                numeroCopias++;
            }
            else{
                numeroComparacao++;
                //Caso 1.2 pt é filho a direita do pai (é feita rotação a esquerda)
                if(ponteiro == paiPt->direita){
                    rotacionaEsquerda(raiz, paiPt);
                    ponteiro = paiPt;
                    paiPt = ponteiro->pai;
                    numeroCopias += 2;
                }
                //Caso 1.3 pt é filho a esquerda do pai (é feita rotação a direita)
                rotacionaDireita(raiz, avoPt);
                swap(paiPt->cor, avoPt->cor);;
                ponteiro = paiPt;
                numeroCopias += 2;
            }
        }
        
        //Caso 2 o pai do pt é filho a direita do avo do pt
        else{
            NoVP *tioPt = avoPt->esquerda;
            numeroCopias++;
            numeroComparacao++;
            //Caso 2.1 o tio do pt tambe é vermelho
            if((tioPt != NULL) && (tioPt->cor == true)){
                avoPt->cor = true;
                paiPt->cor = false;
                tioPt->cor = false;
                ponteiro = avoPt;
                numeroCopias++;
            }
            else{
                numeroComparacao++;
                //Caso 2.2 pt é filho a esquerda do pai (é feita rotação a direita)
                if(ponteiro == paiPt->esquerda){
                    rotacionaDireita(raiz,paiPt);
                    ponteiro=paiPt;
                    paiPt=ponteiro->pai;
                    numeroCopias += 2;
                }
                //Caso 2.3 pt é filho a direita do pai (é feita rotação a esquerda)
                rotacionaEsquerda(raiz,avoPt);
                swap(paiPt->cor, avoPt->cor);
                ponteiro=paiPt;
                numeroCopias += 2;
            }
         }
    }
    raiz->cor=false;
}

//A func˜ao ”Inserir”que passa como parametro o Registro a
//ser inserido na arvore (que contem os dados de ratings.csv)
//e entao a funcao ”Inserir”utiliza a funcao ”AVPInserir”.
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
