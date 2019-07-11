#ifndef ARVOREVP_H
#define ARVOREVP_H
#include "NoVP.h"

class ArvoreVP
{
public:
    ArvoreVP();
    ~ArvoreVP();
    void Inserir(const int &n);
    void Inserir(Registro *registro);
    void emOrdem();
    void nivelOrdem();
    void auxEmOrdem(NoVP *raiz);
    NoVP* AVPInserir(NoVP *raiz, NoVP *pt);
    void auxNivelOrdem(NoVP *raiz);

protected:
    void rotacionaEsquerda(NoVP *&,NoVP *& );
    void rotacionaDireita(NoVP *&,NoVP *& );
    void correcao(NoVP *raiz,NoVP *pt);

private:
    NoVP *raiz;
    unsigned long int numeroComparacao;
    unsigned long int numeroComparacaoBusca;
    unsigned long int numeroCopias;

};

#endif // ARVOREVP_H
