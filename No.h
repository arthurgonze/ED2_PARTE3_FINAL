#ifndef ED2_PARTE3_FINAL_NO_H
#define ED2_PARTE3_FINAL_NO_H

class No
{
private:
    char caracter;
    int freq;
    No *esq;
    No *dir;

public:
    No(char caracter, int freq);
    char getCaracter();
    int getFrequencia();
    No *getEsq();
    No *getDir();
    void setEsq(No *esq);
    void setDir(No *dir);
    void setFreq(int freq);
    void setCaracter(char caracter);
};

#endif //ED2_PARTE3_FINAL_NO_H
