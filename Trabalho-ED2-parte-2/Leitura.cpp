#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include "Leitura.h"
#include "Registro.h"

using namespace std;

Leitura::Leitura()
{
    //ctor
}

Leitura::~Leitura()
{
    //dtor
}

void Leitura::setBytes(int bytes){
    //bytes = bytes;
}


void Leitura::realizarLeitura(int bytes, int N, fstream *myfile, ArvoreVP *arvoreVP){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> random(1, bytes);
    string str;
    string delimitador = ",";
    cout << N << endl;
    for(int i = 0; i < N; i++){
        int contador = 0;
        int userId ;
        int movieId ;
        float rating;
        int timestamp;
        int posicaoRandom = random(generator);
        myfile->seekg(posicaoRandom, ios::beg);
        getline(*myfile, str);
        getline(*myfile, str);
        //cout << "String: " << str << endl;
        int pos = 0;
        istringstream iss;
        string aux;
        while(contador < 3){
            pos = str.find(delimitador);
            if(contador == 0){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> userId;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            else if(contador == 1){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> movieId;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            else if(contador == 2){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> rating;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            contador++;
        }
        iss.str(str);
        iss >> timestamp;
        //cout << "UserId: " << userId << "  movieId: " << movieId << "  Rating: " << rating << "  Timestamp: " << timestamp << endl << endl;
        Registro *novoRegistro = new Registro(userId, movieId, rating, timestamp);
        arvoreVP->Inserir(novoRegistro);
    }
}

void Leitura::realizarLeitura(int bytes, int N, fstream *myfile, ArvoreB *arvoreB){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> random(1, bytes);
    string str;
    string delimitador = ",";
    cout << N << endl;
    for(int i = 0; i < N; i++){
        int contador = 0;
        int userId ;
        int movieId ;
        float rating;
        int timestamp;
        int posicaoRandom = random(generator);
        myfile->seekg(posicaoRandom, ios::beg);
        getline(*myfile, str);
        getline(*myfile, str);
        cout << "String: " << str << endl;
        int pos = 0;
        istringstream iss;
        string aux;
        while(contador < 3){
            pos = str.find(delimitador);
            if(contador == 0){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> userId;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            else if(contador == 1){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> movieId;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            else if(contador == 2){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> rating;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            contador++;
        }
        iss.str(str);
        iss >> timestamp;
        cout << "UserId: " << userId << "  movieId: " << movieId << "  Rating: " << rating << "  Timestamp: " << timestamp << endl << endl;
        Registro *novoRegistro = new Registro(userId, movieId, rating, timestamp);
        //arvoreB->Inserir(novoRegistro);
    }
}
