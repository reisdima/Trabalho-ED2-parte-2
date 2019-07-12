#ifndef LEITURA_H
#define LEITURA_H
#include "ArvoreVP.h"
#include "ArvoreB.h"
#include <fstream>

using namespace std;

class Leitura
{
public:
    static int bytes;
    Leitura();
    ~Leitura();
    static void realizarLeitura(int bytes, int N, fstream *arquivoLeitura, ArvoreVP *arvoreVP);
    static void realizarLeitura(int bytes, int N, fstream *arquivoLeitura, ArvoreB *arvoreB);
    static double realizarBusca(int bytes, int N, fstream *arquivoLeitura, ArvoreB *arvoreB);
    static double realizarBusca(int bytes, int N, fstream *arquivoLeitura, ArvoreVP *arvoreVP);
    static void setBytes(int bytes);
    static void printBytes();
private:

};

//int Leitura::bytes = 0;

#endif // LEITURA_H
