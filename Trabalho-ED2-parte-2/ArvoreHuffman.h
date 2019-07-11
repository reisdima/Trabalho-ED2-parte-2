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
		return l->getFreq() > r->getFreq();
	}
};

class ArvoreHuffman
{
public:
    unordered_map<char, string> huffmanCode;
    ArvoreHuffman(string texto_1);
    ~ArvoreHuffman();
    void auxDestrutor(NoHuffman *no);
    void criaArvoreHuffman();
    void codificador(NoHuffman* raiz, string str);
    void chamaCodificador();
    void imprimiCodigoHuffman();
    float getBytesComprimido(){return bytesComprimido;};
    float getTaxaCompressao(){return taxaCompressao = ((float)taxaCompressao/(float)(texto.size()*8));};
private:
    string texto;
    NoHuffman* raiz;
    float taxaCompressao;
    float bytesComprimido;
    string codificada;

};

#endif // ARVOREHUFFMAN_H
