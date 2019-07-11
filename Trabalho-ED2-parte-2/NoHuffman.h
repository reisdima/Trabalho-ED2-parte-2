#ifndef NOHUFFMAN_H
#define NOHUFFMAN_H


class NoHuffman
{
public:
    NoHuffman();
    NoHuffman(char data_1, int freq_1);
    NoHuffman(char data_1, int freq_1, NoHuffman* left, NoHuffman* right);
    ~NoHuffman();
    NoHuffman* getNoEsq();
    void setNoEsq(NoHuffman* novo);
    NoHuffman* getNoDir();
    void setNoDir(NoHuffman* novo);
    int getFreq();
    char getData();
    void setFreq(int novaF);
    void setData(char novaD);

private:
    char data; //char do nó
    int freq; //frequencia do no
    NoHuffman *esq, *dir;
};

#endif // NOHUFFMAN_H
