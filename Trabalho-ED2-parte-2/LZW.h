#ifndef LZW_H
#define LZW_H
#include <iostream>
#include <vector>

using namespace std;

class LZW
{
public:
    LZW(string texto);
    ~LZW();
    void codificar();
    void imprimirCodigo();
    int getBytesComprimido();
    float getTaxaCompressao();

private:
    string texto;
    vector<int> codigoLZW;
    float taxaCompressao;
    float bytesComprimido;
};

#endif // LZW_H
