#ifndef ED2_PARTE3_FINAL_CONTROLAARQUIVO_H
#define ED2_PARTE3_FINAL_CONTROLAARQUIVO_H

#include "question.h"

class controlaArquivo
{
public:
    controlaArquivo();
    virtual ~controlaArquivo();
    question *importaQuestoes(int numQuestoes);
    int *importaIds(int numQuestoes);
    void imprimeSaida(string nome, int tamanho, double tempoGasto, long long unsigned tamanhoDoArquivoEmBytes);
    string *vetorDeBodys(int numQuestoes);
    void imprimeBodys(string *vetorDeBodys, int tamanho, string nomeDoArquivo);
    void imprimeBodysBinarios(string *vetorDeBodys, int tamanho, string nomeDoArquivo);
    void imprimeBodys(string *vetorDeBodys, int tamanho, string nomeDoArquivo, int tamDoArquivoEmBits);
protected:
private:
    int converteEmNumero(string texto);
    string isolaConteudo(char buffer[], int i);
};

#endif //ED2_PARTE3_FINAL_CONTROLAARQUIVO_H
