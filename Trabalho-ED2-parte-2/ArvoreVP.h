#ifndef ARVOREVP_H
#define ARVOREVP_H
#include "NoVP.h"

class ArvoreVP
{
public:
    ArvoreVP();
    ~ArvoreVP();
    void Inserir(Registro *registro);

private:
    NoVP *raiz;
};

#endif // ARVOREVP_H
