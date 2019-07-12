#ifndef ARVOREHUFFMAN_H
#define ARVOREHUFFMAN_H
#include <unordered_map>
#include "NoHuffman.h"


using namespace std;


//Struct usada para comparar e ordenar a heap
struct comp
{
	bool operator()(NoHuffman* l, NoHuffman* r)
	{
		return l->getFrequencia() > r->getFrequencia();
	}
};

class ArvoreHuffman
{
public:
    unordered_map<char, string> huffmanCode;
    ArvoreHuffman(string texto);
    ~ArvoreHuffman();
    void auxDestrutor(NoHuffman *no);

    void criarArvoreHuffman();
    void codificador(NoHuffman* raiz, string str);
    void chamarCodificador();
    void imprimirCodigoHuffman();

    float getBytesComprimido(){return bytesComprimido;};
    float getTaxaCompressao();

private:
    string texto;
    NoHuffman* raiz;
    float taxaCompressao;
    float bytesComprimido;
    string codificada;

};

#endif // ARVOREHUFFMAN_H
