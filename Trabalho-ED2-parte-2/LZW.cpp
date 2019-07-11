#include <vector>
#include <bits/stdc++.h>
#include "LZW.h"

LZW::LZW(string texto)
{
    this->texto = texto;
}

LZW::~LZW()
{
    //dtor
}


void LZW::codificar(){
    unordered_map<string, int> tabela;
    for(int i = 0; i < 255; i ++){
        string aux = "";
        aux += char(i);
        tabela[aux] = i;
    }
    string p = "";
    string c = "";
    int proxIndex = 256;
    for(int i = 0; i < texto.length(); i ++){
        c += texto[i];
        //if (i != texto.length() - 1)
          //  c += texto[i + 1];
        if(tabela.find(p + c) != tabela.end())
            p = p + c;
        else{
            //cout << "Nao achou\t" << p+c << "\t\t" << endl;

            codigoLZW.push_back(tabela[p]);
            tabela[p+c] = proxIndex;
            proxIndex++;
            p = c;
        }
        c = "";
    }
    //cout << p << "\t";
    codigoLZW.push_back(tabela[p]);
}

void LZW::imprimirCodigo(){
    cout<<endl<<endl<<"CODIGO LZW"<<endl<<endl;
    for (int i = 0; i < codigoLZW.size(); i++) {
        cout << codigoLZW[i] << " ";
    }
}


float LZW::getTaxaCompressao(){
    return taxaCompressao = ((float)bytesComprimido/(float)(texto.size()));
}

int LZW::getBytesComprimido(){
    int contaDigitos = 0, valor;
    for (int i = 0; i < codigoLZW.size(); i++)
    {
        valor = codigoLZW[i];
        if (valor == 0) contaDigitos = 1;
        else
        {
            while (valor != 0)
            {
              contaDigitos = contaDigitos + 1;
              valor = valor / 10;
            }
        }
    }
    bytesComprimido = contaDigitos;
    return bytesComprimido;
}
