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

private:
    string texto;
    vector<int> codigoLZW;
};

#endif // LZW_H
