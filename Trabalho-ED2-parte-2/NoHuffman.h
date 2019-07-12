#ifndef NOHUFFMAN_H
#define NOHUFFMAN_H


class NoHuffman
{
public:
    NoHuffman();
    NoHuffman(char data, int frequencia);
    NoHuffman(char data, int frequencia, NoHuffman* left, NoHuffman* right);
    ~NoHuffman();
    NoHuffman* getNoEsq();
    void setNoEsq(NoHuffman* novo);
    NoHuffman* getNoDir();
    void setNoDir(NoHuffman* novo);

    int getFrequencia();
    char getData();

    void setFrequencia(int frequencia);
    void setData(char data);

private:
    char data;
    int frequencia;
    NoHuffman *esq;
    NoHuffman *dir;
};

#endif // NOHUFFMAN_H
