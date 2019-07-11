#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Leitura.h"
#include "Menu.h"
#include "LZW.h"
using namespace std;

Menu::Menu()
{
    this->vetorN = NULL;
    this->tamanhoN = 0;
}

Menu::~Menu()
{
    //dtor
}


void Menu::ExibirMenu(){
    int escolha = -1;
    leituraN();
    cout << "Insira o que deseja fazer: " << endl;
    while(escolha != 0){
        cout << endl << "1. Arvore VP" << endl;
        cout << "2. Arvore B" << endl;
        cout << "0. Encerrar o programa" << endl << endl;
        cin >> escolha;
        switch(escolha){
        case 1:
            Parte1_ArvoreVP();
            break;
        case 2:
            Parte1_ArvoreB();
            break;
        case 0:
            break;
        default:
            cout << endl <<  "Por favor insira um valor correto" << endl;
        }
    }
}

void Menu::Parte1_ArvoreB(){
    unsigned long int numeroComparacao[tamanhoN];
    unsigned long int numeroCopias[tamanhoN];
    double tempoTotal[tamanhoN];
    for(int i = 0; i < tamanhoN; i ++){
         numeroComparacao[i] = 0;
         numeroCopias[i] = 0;
         tempoTotal[i] = 0;
    }
    fstream myfile;
    ofstream arquivoSaida;
	myfile.open("ratings.csv");
	arquivoSaida.open("arvoreB.txt");
	if(myfile.is_open() && arquivoSaida.is_open()){
        myfile.seekg(0, ios::end);
        int bytes = myfile.tellg();
        for(int i = 0; i < tamanhoN; i++){
            cout << "PARA N = " << vetorN[i] << endl << endl;
            arquivoSaida << "PARA N = " << vetorN[i] << endl << endl;
            for(int j = 0; j < 5; j++){
                ArvoreB *arvoreB = new ArvoreB(2);
                std::chrono::time_point<std::chrono::system_clock> comeco, fim;
                comeco = std::chrono::system_clock::now();
                Leitura::realizarLeitura(bytes, vetorN[i], &myfile, arvoreB);
                fim = std::chrono::system_clock::now();
                double total = std::chrono::duration_cast<std::chrono::milliseconds>(fim - comeco).count();
                tempoTotal[i] += total;
                numeroComparacao[i] += arvoreB->getNumeroComparacao();
                numeroCopias[i] += arvoreB->getNumeroCopias();
            }
            cout << "Tempo total para as 5 iteracoes: " << tempoTotal[i] << endl;
            cout << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            cout << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            cout << "Media de tempo para as 5 iteracoes: " << tempoTotal[i]/5 << endl;
            cout << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            cout << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
            arquivoSaida << "Tempo total para as 5 iteracoes: " << tempoTotal[i] << endl;
            arquivoSaida << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            arquivoSaida << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            arquivoSaida << "Media de tempo para as 5 iteracoes: " << tempoTotal[i]/5 << endl;
            arquivoSaida << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            arquivoSaida << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
        }
	}
	else{
        cout << "Arquivo nao encontrado" << endl;
	}
}

void Menu::Parte1_ArvoreVP(){
    unsigned long int numeroComparacao[tamanhoN];
    unsigned long int numeroCopias[tamanhoN];
    double tempoTotal[tamanhoN];
    for(int i = 0; i < tamanhoN; i ++){
        cout << vetorN[i] << endl;
        numeroComparacao[i] = 0;
        numeroCopias[i] = 0;
        tempoTotal[i] = 0;
    }
    fstream myfile;
    ofstream arquivoSaida;
	myfile.open("ratings.csv");
	arquivoSaida.open("arvoreVP.txt");
	if(myfile.is_open() && arquivoSaida.is_open()){
        myfile.seekg(0, ios::end);
        int bytes = myfile.tellg();
        for(int i = 0; i < tamanhoN; i++){
            cout << "PARA N = " << vetorN[i] << endl << endl;
            arquivoSaida << "PARA N = " << vetorN[i] << endl << endl;
            for(int j = 0; j < 5; j++){
                ArvoreVP *arvoreVP = new ArvoreVP();
                std::chrono::time_point<std::chrono::system_clock> comeco, fim;
                comeco = std::chrono::system_clock::now();
                Leitura::realizarLeitura(bytes, vetorN[i], &myfile, arvoreVP);
                fim = std::chrono::system_clock::now();
                double total = std::chrono::duration_cast<std::chrono::milliseconds>(fim - comeco).count();
                tempoTotal[i] += total;
                numeroComparacao[i] += arvoreVP->getNumeroComparacao();
                numeroCopias[i] += arvoreVP->getNumeroCopias();
            }
            cout << "Tempo total para as 5 iteracoes: " << tempoTotal[i] << endl;
            cout << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            cout << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            cout << "Media de tempo para as 5 iteracoes: " << tempoTotal[i]/5 << endl;
            cout << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            cout << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
            arquivoSaida << "Tempo total para as 5 iteracoes: " << tempoTotal[i] << endl;
            arquivoSaida << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            arquivoSaida << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            arquivoSaida << "Media de tempo para as 5 iteracoes: " << tempoTotal[i]/5 << endl;
            arquivoSaida << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            arquivoSaida << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
            cout << endl << endl;
            arquivoSaida << endl << endl;
        }
        arquivoSaida.close();
	}
	else{
        cout << "Arquivo nao encontrado" << endl;
	}
}

void Menu::Parte1(){
    fstream myfile;
	myfile.open("ratings.csv");
	if(myfile.is_open()){
        myfile.seekg(0, ios::end);
        int bytes = myfile.tellg();
        for(int i = 0; i < 10; i ++){
            for(int j = 0; j < 50; j++){
            for(int j = 0; j < 1; j++){
                ArvoreVP *arvoreVP = new ArvoreVP();
                Leitura::realizarLeitura(bytes, vetorN[i], &myfile, arvoreVP);
            }
            }
        }
	}
	else{
        cout << "Arquivo nao encontrado" << endl;
	}
}

void Menu::Parte2(){
    cout << "Parte 2" << endl;
    string texto = "bananabanabofanas";
    //LZW teste(texto);
    //teste.codificar();
    //teste.imprimirCodigo();

}

void Menu::leituraN(){
    fstream entradaN;
    entradaN.open("entrada.txt");
    if(entradaN.is_open()){
        string aux;
        getline(entradaN, aux);
        istringstream iss;
        iss.str(aux);
        iss >> tamanhoN;
        iss.clear();
        int k = 0;
        vetorN = new int(tamanhoN);
        for(int i = 0; i < tamanhoN; i++){
            int auxInt;
            getline(entradaN, aux);
            iss.str(aux);
            iss >> auxInt;
            iss.clear();
            vetorN[i] = auxInt;
        }
        for(int i = 0 ; i < tamanhoN; i++)
            cout << vetorN[i] << endl;
    }
}
