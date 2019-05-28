#ifndef NOVP_H
#define NOVP_H
#include "Registro.h"


class NoVP
{
public:
    NoVP(Registro *registro);
    ~NoVP();
    void setCor(int cor);

    int getMovieId();
    int getUserId();

private:
    int cor; //0 = preto; 1 = vermelho
    Registro *registro;
};

#endif // NOVP_H
