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



void Leitura::realizarLeitura(int bytes, int N, fstream *myfile, ArvoreVP *arvoreVP){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> random(1, bytes);
    string str;
    string delimitador = ",";
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
                arvoreB->Inserir(novoRegistro);
        }
}


double Leitura::realizarBusca(int bytes, int N, fstream *arquivoLeitura, ArvoreB *arvoreB){
        vector<Registro> vetor;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        uniform_int_distribution<uint32_t> random(1, bytes);
        string str;
        string delimitador = ",";
        for(int i = 0; i < N; i++){
                int contador = 0;
                int userId ;
                int movieId ;
                float rating;
                int timestamp;
                int posicaoRandom = random(generator);
                arquivoLeitura->seekg(posicaoRandom, ios::beg);
                getline(*arquivoLeitura, str);
                getline(*arquivoLeitura, str);
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
                Registro *registro = new Registro(userId, movieId, rating, timestamp);
                vetor.push_back(*registro);
        }
        std::chrono::time_point<std::chrono::system_clock> comeco, fim;
        comeco = std::chrono::system_clock::now();
        for(int i = 0; i < vetor.size(); i++){
                arvoreB->Buscar(&vetor[i]);
        }
        fim = std::chrono::system_clock::now();

        double total = std::chrono::duration_cast<std::chrono::milliseconds>(fim - comeco).count();
        return total;
}

double Leitura::realizarBusca(int bytes, int N, fstream *arquivoLeitura, ArvoreVP *arvoreVP){
                vector<Registro> vetor;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        uniform_int_distribution<uint32_t> random(1, bytes);
        string str;
        string delimitador = ",";
        for(int i = 0; i < N; i++){
                int contador = 0;
                int userId ;
                int movieId ;
                float rating;
                int timestamp;
                int posicaoRandom = random(generator);
                arquivoLeitura->seekg(posicaoRandom, ios::beg);
                getline(*arquivoLeitura, str);
                getline(*arquivoLeitura, str);
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
                Registro *registro = new Registro(userId, movieId, rating, timestamp);
                vetor.push_back(*registro);
        }
        std::chrono::time_point<std::chrono::system_clock> comeco, fim;
        comeco = std::chrono::system_clock::now();
        for(int i = 0; i < vetor.size(); i++){
                arvoreVP->Buscar(&vetor[i]);
        }
        fim = std::chrono::system_clock::now();

        double total = std::chrono::duration_cast<std::chrono::milliseconds>(fim - comeco).count();
        return total;
}
