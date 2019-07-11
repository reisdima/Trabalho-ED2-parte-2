#ifndef ARVOREB_H
#define ARVOREB_H
#include "NoB.h"
#include "Registro.h"

class ArvoreB
{
public:
    ArvoreB(int d);
    ~ArvoreB();

    //Funções
    void Inserir(Registro *registro);
    bool Buscar(Registro *registro);
    bool Buscar(Registro *registro, NoB **pt, int *posicaoChave);
    void Cisao(Registro *registro, NoB **pt, int posicaoChave, NoB *outroNo);
    void inserirNaoCheio(Registro *registro, NoB **pt, int posicaoChave);
    int Inserir(Registro *registro, NoB **pt);

    unsigned long int getNumeroComparacao();
    unsigned long int getNumeroComparacaoBusca();
    unsigned long int getNumeroCopias();


private:
    NoB *raiz;
    int d;
    unsigned long int numeroComparacao;
    unsigned long int numeroComparacaoBusca;
    unsigned long int numeroCopias;



};

#endif // ARVOREB_H
