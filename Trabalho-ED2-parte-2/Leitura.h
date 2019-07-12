#ifndef LEITURA_H
#define LEITURA_H
#include "ArvoreVP.h"
#include "ArvoreB.h"
#include <fstream>

using namespace std;
/** Classe auxiliar para leitura de arquivo
 *  e insercao e busca em arvores
 *
 */

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
private:

};

//int Leitura::bytes = 0;

#endif // LEITURA_H
