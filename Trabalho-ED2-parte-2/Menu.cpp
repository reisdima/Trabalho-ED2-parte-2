#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>

#include "ArvoreHuffman.h"
#include "Leitura.h"
#include "LZW.h"
#include "Menu.h"
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
        case 3:
            Parte2_LZW();
            break;
        case 4:
            Parte2_Huffman();
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
    unsigned long int numeroComparacaoBusca[tamanhoN];
    unsigned long int numeroCopias[tamanhoN];
    double tempoTotalInsercao[tamanhoN];
    double tempoTotalBusca[tamanhoN];
    for(int i = 0; i < tamanhoN; i ++){
         numeroComparacao[i] = 0;
         numeroComparacaoBusca[i] = 0;
         numeroCopias[i] = 0;
         tempoTotalInsercao[i] = 0;
         tempoTotalBusca[i] = 0;
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

                tempoTotalBusca[i] += Leitura::realizarBusca(bytes, vetorN[i], &myfile, arvoreB);
                numeroComparacaoBusca[i] += arvoreB->getNumeroComparacaoBusca();

                double tempoInsercao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - comeco).count();
                tempoTotalInsercao[i] += tempoInsercao;
                numeroComparacao[i] += arvoreB->getNumeroComparacao();
                numeroCopias[i] += arvoreB->getNumeroCopias();
            }
            cout << "Tempo total para as 5 iteracoes: " << tempoTotalInsercao[i] << endl;
            cout << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            cout << "Numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i] << endl;
            cout << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            cout << "Media de tempo para as 5 iteracoes: " << tempoTotalInsercao[i]/5 << endl;
            cout << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            cout << "Media do numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i]/5 << endl;
            cout << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
            arquivoSaida << "Tempo total para as 5 iteracoes: " << tempoTotalInsercao[i] << endl;
            arquivoSaida << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            arquivoSaida << "Numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i] << endl;
            arquivoSaida << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            arquivoSaida << "Media de tempo para as 5 iteracoes: " << tempoTotalInsercao[i]/5 << endl;
            arquivoSaida << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            arquivoSaida << "Media do numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i]/5 << endl;
            arquivoSaida << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
        }
	}
	else{
        cout << "Arquivo nao encontrado" << endl;
	}
}

void Menu::Parte1_ArvoreVP(){
    unsigned long int numeroComparacao[tamanhoN];
    unsigned long int numeroComparacaoBusca[tamanhoN];
    unsigned long int numeroCopias[tamanhoN];
    double tempoTotalInsercao[tamanhoN];
    double tempoTotalBusca[tamanhoN];
    for(int i = 0; i < tamanhoN; i ++){
         numeroComparacao[i] = 0;
         numeroComparacaoBusca[i] = 0;
         numeroCopias[i] = 0;
         tempoTotalInsercao[i] = 0;
         tempoTotalBusca[i] = 0;
    }
    fstream myfile;
    ofstream arquivoSaida;
	myfile.open("ratings.csv");
	arquivoSaida.open("arvoreVP.txt");
	if(myfile.is_open() && arquivoSaida.is_open()){
        myfile.seekg(0, ios::end);
        int bytes = myfile.tellg();
        for(int i = 0; i < 1; i++){
            cout << "PARA N = " << vetorN[i] << endl << endl;
            arquivoSaida << "PARA N = " << vetorN[i] << endl << endl;
            for(int j = 0; j < 5; j++){
                ArvoreVP *arvoreVP = new ArvoreVP();

                std::chrono::time_point<std::chrono::system_clock> comeco, fim;

                comeco = std::chrono::system_clock::now();
                Leitura::realizarLeitura(bytes, vetorN[i], &myfile, arvoreVP);
                fim = std::chrono::system_clock::now();

                tempoTotalBusca[i] += Leitura::realizarBusca(bytes, vetorN[i], &myfile, arvoreVP);
                numeroComparacaoBusca[i] += arvoreVP->getNumeroComparacaoBusca();

                double tempoInsercao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - comeco).count();
                tempoTotalInsercao[i] += tempoInsercao;
                numeroComparacao[i] += arvoreVP->getNumeroComparacao();
                numeroCopias[i] += arvoreVP->getNumeroCopias();
            }
            cout << "Tempo total para as 5 iteracoes: " << tempoTotalInsercao[i] << endl;
            cout << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            cout << "Numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i] << endl;
            cout << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            cout << "Media de tempo para as 5 iteracoes: " << tempoTotalInsercao[i]/5 << endl;
            cout << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            cout << "Media do numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i]/5 << endl;
            cout << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
            arquivoSaida << "Tempo total para as 5 iteracoes: " << tempoTotalInsercao[i] << endl;
            arquivoSaida << "Numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i] << endl;
            arquivoSaida << "Numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i] << endl;
            arquivoSaida << "Numero de copia para as 5 iteracoes: " << numeroCopias[i] << endl;
            arquivoSaida << "Media de tempo para as 5 iteracoes: " << tempoTotalInsercao[i]/5 << endl;
            arquivoSaida << "Media do numero de comparacoes para as 5 iteracoes: " << numeroComparacao[i]/5 << endl;
            arquivoSaida << "Media do numero de comparacoes ao fazer busca para as 5 iteracoes: " << numeroComparacaoBusca[i]/5 << endl;
            arquivoSaida << "Media do numero de copia para as 5 iteracoes: " << numeroCopias[i]/5 << endl;
        }
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


void Menu::Parte2_LZW(){
    fstream file("movies_metadata.csv");
    if(!file)
    {
        cout<<"Arquivo movies_metadata nao encontrado"<<endl;
        exit(0);
    }
    ofstream file2("SaidaLZW.txt",ios::out);
    string buffer;
    vector<vector<string> > linhas; //vetor de vetor para toads as linhas

    char delimitador = ',';
    char delimitador_2 = '"'; //Se tem ',' dentro de um " " essa virgula nao significa outra coluna.
    int i=0;
    while(!file.eof()){
        getline(file, buffer); //ler cada linha
        stringstream ss(buffer); //colocar a linha lida num stringstream

        vector<string> linha; //iniciar o vetor da linha
        bool flag = false;
        while(getline(ss, buffer)) { //ler cada coluna

            int start = 0;

            for(i = 0; i < buffer.length(); i++) {

                if(buffer[i] == delimitador) {

                    linha.push_back(buffer.substr(start, i-start));
                    start = i+1;
                }

                else if(buffer[i] == delimitador_2)
                {
                    for(i = i+1; i <= buffer.length(); i++)
                    {
                        if(i==buffer.length())
                        {
                            flag = true;
                            linha.push_back(buffer.substr(start, (i-1)-start));
                            break;
                        }

                        if(buffer[i] == delimitador_2 && buffer[i+1] == delimitador)
                        {
                            linha.push_back(buffer.substr(start, i-start+1));
                            i++;
                            start = i+1;
                            break;
                        }
                    }
                    if(i>buffer.length())
                       break;
                }
            }

            if(i - start != 0 && flag ==false)
            {
                    linha.push_back(buffer.substr(start, (i-1)-start));
            }
        }
        linhas.push_back(linha);
    }
        cout<< "------------  Compressao LZW ----------------"<<endl<<endl;
    int numLinhas = linhas.size();
    cout <<  "Num: " << numLinhas << endl;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();    //seed para gerar numeros aleatorios sempre (relogio do computador)
    std::default_random_engine generator(seed);                                         //gerador de numeros aleatorios com a semente
    std::uniform_int_distribution<int> distribution(1,numLinhas);                       //gera um numero aleatorio

    unsigned long int vetTotalBytes[tamanhoN]; //Armazena os totais de bytes nao comprimidos
    unsigned long int vetTotalBytesComp[tamanhoN];  //Armazena os totais de bytes comprimidos
    double vetTempoTotal[tamanhoN];  //Armazena os tempos totais
    double vetRazaoCompressao[tamanhoN];
    unsigned long int totalBytes = 0; //total de bytes nao compimidos
    unsigned long int totalBytesComp = 0; //total de bytes comprimidos
    double razaoCompressao = 0;
    double tempoTotal = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end; //inicializa as variaveis para guardar o tempo
    int aleatorio = 0;

    for(int k=0; k<tamanhoN ; k++){
        cout<<"N: "<<vetorN[k]<<endl<<endl;

        totalBytes = 0; //total de bytes nao compimidos
        totalBytesComp = 0; //total de bytes comprimidos
        razaoCompressao = 0;
        tempoTotal = 0;
        string textoTotal;
        for(int l=1; l<=vetorN[k] ; l++){
            aleatorio = distribution(generator); //pega a linha aleatoria
            bool flg = false;

            while(flg == false){
                if(linhas[aleatorio].size() == 24){ //Checa qual registro está completo,ou seja, apresenta um numero de colunas igual dos indices, ja que registros incompletos causam crash's
                    if(linhas[aleatorio][9].size() > 3){ //Checa se sinopse nao está vazia
                        flg = true;
                        string texto = linhas[aleatorio][9].substr(1, linhas[aleatorio][9].size() - 2); //mostrar sem as " "
                        if(l%50 == 0){
                            start = std::chrono::system_clock::now(); //inicia cronometro
                            LZW *lzw = new LZW(textoTotal);
                            lzw->codificar();
                            end = std::chrono::system_clock::now(); //para cronometro
                            tempoTotal += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //calcula tempo decorrido

                            totalBytesComp += lzw->getBytesComprimido(); //adiciona o total de bytes do texto apos comprimir
                            razaoCompressao += lzw->getTaxaCompressao(); //soma as razoes de compressao.

                            textoTotal.erase(0,textoTotal.length());
                        }
                        else{
                            textoTotal+=texto;
                            totalBytes += textoTotal.length(); //adiciona o total de bytes do texto sem comprimir
                        }
                        break;
                    }

                }
                aleatorio = distribution(generator); //pega a linha aleatoria
            }
        }

        cout<<"Total Bytes: "<<totalBytes<<endl;
        cout<<"Total Bytes Comprimido: "<<totalBytesComp<<endl;
        cout<<"Razao de Compressao Media: "<<razaoCompressao/(float)vetorN[k]<<endl;
        cout<<"Tempo Total: "<<tempoTotal<<"ms"<<endl;

        vetTotalBytes[k] = totalBytes;
        vetTotalBytesComp[k] = totalBytesComp;
        vetRazaoCompressao[k] = razaoCompressao/(float)(vetorN[k]);
        vetTempoTotal[k] = tempoTotal;
        cout<<endl<<"-----------------"<<endl;
    }


    cout<<"----------------- METRICAS LZW ------------------"<<endl;
    file2<<"----------------- METRICAS LZW ------------------"<<endl;
    for(int k=0; k<tamanhoN ; k++){
        cout<<endl<<endl;
        cout<<" N = " << vetorN[k] << ": "<<endl;
        cout<<"-------------------------------------------------" <<endl;
        cout<<"|     METRICAS       |            LZW           |" <<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|     TOTAL BYTES    |"<< vetTotalBytes[k] << "\t\t\t|" <<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|  TOTAL BYTES COMP  |"<< vetTotalBytesComp[k] <<"\t\t\t|"<<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|     RAZAO COMP     |"<< vetRazaoCompressao[k] <<"\t\t\t| "<<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|     TEMPO TOTAL    |"<< vetTempoTotal[k] <<" ms \t\t\t| "<<endl;
        cout<<"-------------------------------------------------" <<endl;

         file2<<endl<<endl;
        file2<<" N = " << vetorN[k] << ": "<<endl;
        file2<<"-------------------------------------------------" <<endl;
        file2<<"|     METRICAS       |            LZW           |" <<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|     TOTAL BYTES    |"<< vetTotalBytes[k] << "\t\t\t|" <<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|  TOTAL BYTES COMP  |"<< vetTotalBytesComp[k] <<"\t\t\t|"<<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|     RAZAO COMP     |"<< vetRazaoCompressao[k] <<"\t\t\t| "<<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|     TEMPO TOTAL    |"<< vetTempoTotal[k] <<" ms \t\t\t| "<<endl;
        file2<<"-------------------------------------------------" <<endl;
    }
}



void Menu::Parte2_Huffman(){
        //******************************************************
    //*                                                    *
    //*                Compressao Huffman                  *
    //*                                                    *
    //******************************************************

    /**
        - Leitura do Arquivo
       A leitura de arquivo funciona a partir de um vector de vector chamado linhas que vai guardar todas as linhas do arquivo.
       Existe um vector chamado linha que armazena a informacao de cada coluna do arquivo.
       Assim é feito a leitura e armazenamento nesses vectors, obedecendo os chars delimitadores e enclosures.
    */
    fstream file("movies_metadata.csv");
    if(!file)
    {
        cout<<"Arquivo movies_metadata nao encontrado"<<endl;
        exit(0);
    }
    ofstream file2("saidaHuffman.txt",ios::out);
    string buffer;
    vector<vector<string> > linhas; //vetor de vetor para toads as linhas

    char delimitador = ',';
    char delimitador_2 = '"'; //Se tem ',' dentro de um " " essa virgula nao significa outra coluna.
    int i=0;
    while(!file.eof())
    {
        getline(file, buffer); //ler cada linha
        stringstream ss(buffer); //colocar a linha lida num stringstream

        vector<string> linha; //iniciar o vetor da linha
        bool flag = false;
        while(getline(ss, buffer)) { //ler cada coluna

            int start = 0;

            for(i = 0; i < buffer.length(); i++) {

                if(buffer[i] == delimitador) {

                    linha.push_back(buffer.substr(start, i-start));
                    start = i+1;
                }

                else if(buffer[i] == delimitador_2)
                {
                    for(i = i+1; i <= buffer.length(); i++)
                    {
                        if(i==buffer.length())
                        {
                            flag = true;
                            linha.push_back(buffer.substr(start, (i-1)-start));
                            break;
                        }

                        if(buffer[i] == delimitador_2 && buffer[i+1] == delimitador)
                        {
                            linha.push_back(buffer.substr(start, i-start+1));
                            i++;
                            start = i+1;
                            break;
                        }
                    }
                    if(i>buffer.length())
                       break;
                }
            }

            if(i - start != 0 && flag ==false)
            {
                    linha.push_back(buffer.substr(start, (i-1)-start));
            }
        }
        linhas.push_back(linha);
    }
    /**
        Finaliza Leitura e Armazenamento
    */



    /**
        - Elaboracao Huffman
        Gera um número aleatório de qual registro(linha) será pego e acessa a coluna 9, que é a que está a sinopse.
        Após isso é feita a compressao do texto e armazenado as métricas para comparacao.
    */

    cout<< "------------  Compressao Huffman ----------------"<<endl<<endl;
    int numLinhas = linhas.size();

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();    //seed para gerar numeros aleatorios sempre (relogio do computador)
    std::default_random_engine generator(seed);                                         //gerador de numeros aleatorios com a semente
    std::uniform_int_distribution<int> distribution(1,numLinhas);                       //gera um numero aleatorio

    unsigned long int vetTotalBytes[tamanhoN]; //Armazena os totais de bytes nao comprimidos
    unsigned long int vetTotalBytesComp[tamanhoN];  //Armazena os totais de bytes comprimidos
    double vetTempoTotal[tamanhoN];  //Armazena os tempos totais
    double vetRazaoCompressao[tamanhoN];

    unsigned long int totalBytes = 0; //total de bytes nao compimidos
    unsigned long int totalBytesComp = 0; //total de bytes comprimidos
    double razaoCompressao = 0;
    double tempoTotal = 0;

    std::chrono::time_point<std::chrono::system_clock> start, end; //inicializa as variaveis para guardar o tempo
    int aleatorio = 0;

    for(int k=0; k<tamanhoN ; k++){
        cout<<"N: "<<vetorN[k]<<endl<<endl;

        totalBytes = 0; //total de bytes nao compimidos
        totalBytesComp = 0; //total de bytes comprimidos
        razaoCompressao = 0;
        tempoTotal = 0;

        for(int l=0; l<vetorN[k] ; l++){
            aleatorio = distribution(generator); //pega a linha aleatoria
            bool flg = false;

            while(flg == false){
                if(linhas[aleatorio].size() == 24){ //Checa qual registro está completo,ou seja, apresenta um numero de colunas igual dos indices, ja que registros incompletos causam crash's

                    if(linhas[aleatorio][9].size() > 3){//Checa se sinopse nao está vazia
                        flg = true;
                        string texto = linhas[aleatorio][9].substr(1, linhas[aleatorio][9].size() - 2); //mostrar sem as " "
                        totalBytes += texto.length(); //adiciona o total de bytes do texto sem comprimir
                        ArvoreHuffman* arv = new ArvoreHuffman(texto);

                        start = std::chrono::system_clock::now(); //inicia cronometro
                        arv->criarArvoreHuffman();
                        arv->chamarCodificador();
                        end = std::chrono::system_clock::now(); //para cronometro

                        tempoTotal += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //calcula tempo decorrido

                        razaoCompressao += arv->getTaxaCompressao(); //soma as razoes de compressao.
                        totalBytesComp += arv->getBytesComprimido(); //adiciona o total de bytes do texto apos comprimir

                        delete arv;

                        break;
                    }

                }
                aleatorio = distribution(generator); //pega a linha aleatoria
            }
        }

        cout << "Total Bytes: " << totalBytes << endl;
        cout << "Total Bytes Comprimido: " << totalBytesComp << endl;
        cout << "Razao de Compressao Media: "<<razaoCompressao/(float)vetorN[k] << endl;
        cout << "Tempo Total: " << tempoTotal << "ms" << endl;

        vetTotalBytes[k] = totalBytes;
        vetTotalBytesComp[k] = totalBytesComp;
        vetRazaoCompressao[k] = razaoCompressao/(float)vetorN[k];
        vetTempoTotal[k] = tempoTotal;
        cout<<endl<<"-----------------"<<endl;
    }

    cout<<"----------------- METRICAS HUFFMAN ------------------"<<endl;


    file2<<"----------------- METRICAS HUFFMAN ------------------"<<endl;

    for(int k=0; k<tamanhoN ; k++){
        cout<<endl<<endl;
        cout<<" N = " << vetorN[k] << ": "<<endl;
        cout<<"-------------------------------------------------" <<endl;
        cout<<"|     METRICAS       |         HUFFMAN          |" <<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|     TOTAL BYTES    |"<< vetTotalBytes[k] << "\t\t\t|" <<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|  TOTAL BYTES COMP  |"<< vetTotalBytesComp[k] <<"\t\t\t|"<<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|     RAZAO COMP     |"<< vetRazaoCompressao[k] <<"\t\t\t| "<<endl;
        cout<<"|--------------------|--------------------------|" <<endl;
        cout<<"|     TEMPO TOTAL    |"<< vetTempoTotal[k] <<" ms \t\t\t| "<<endl;
        cout<<"-------------------------------------------------" <<endl;

        file2<<endl<<endl;
        file2<<" N = " << vetorN[k] << ": "<<endl;
        file2<<"-------------------------------------------------" <<endl;
        file2<<"|     METRICAS       |         HUFFMAN          |" <<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|     TOTAL BYTES    |"<< vetTotalBytes[k] << "\t\t\t|" <<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|  TOTAL BYTES COMP  |"<< vetTotalBytesComp[k] <<"\t\t\t|"<<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|     RAZAO COMP     |"<< vetRazaoCompressao[k] <<"\t\t\t| "<<endl;
        file2<<"|--------------------|--------------------------|" <<endl;
        file2<<"|     TEMPO TOTAL    |"<< vetTempoTotal[k] <<" ms \t\t\t| "<<endl;
        file2<<"-------------------------------------------------" <<endl;

    }
}
