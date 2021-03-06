#include <iostream>
#include "controlaArquivo.h"
#include "LZW.h"
#include "ArvHuffman.h"
#include "LZ77.h"
#include "LZ78.h"

using namespace std;

int main()
{
    int tam[6] = {1000, 5000, 10000, 50000, 100000, 500000};
    string descricao[6] = {"1", "5k", "10k", "50k", "100k", "500k"};
    int i = 0; //posição em tam
    controlaArquivo controleDeArquivo;

    long double tempoHuffman = 0;
    long double tempoLZ77 = 0;
    long double tempoLZ78 = 0;
    long double tempoLZW = 0;
    clock_t fim, start;

    for (i; i < 6; i++)
    {
        cout<<"teste"<<endl;
        string *vetorQuestoes = controleDeArquivo.vetorDeBodys(tam[i]);
        string *vetorCompressoes = new string[tam[i]];


        /************
        * Originais *
        ************/

        //Vamos salvar os bodys sem comprimir, para comparar depois
        string nomeDoArquivo = "originais" + descricao[i];
        cout << "Imprimindo bodys em " + nomeDoArquivo << endl;
        controleDeArquivo.imprimeBodys(vetorQuestoes, tam[i], nomeDoArquivo);


        /**********
        * Huffman *
        **********/

        //comprime
        cout << "Comprimindo com Huffman" << endl;

        ArvHuffman *huffman = new ArvHuffman();

        start = clock();
        long long unsigned tamDoArquivoEmBytesHuffman = 0;
        for (int j = 0; j < tam[i]; j++)
        {
            vetorCompressoes[j] = huffman->retornaStringComprimida(vetorQuestoes[j]);
            tamDoArquivoEmBytesHuffman += vetorCompressoes[j].size();
        }
        fim = clock();
        tempoHuffman = 1000*(fim - start)/(CLOCKS_PER_SEC);
        delete huffman;
        //salva em disco
        //calcula
        tamDoArquivoEmBytesHuffman = tamDoArquivoEmBytesHuffman/8;
        nomeDoArquivo = "huffman" + descricao[i];
        cout << "Imprimindo bodys em " + nomeDoArquivo << endl;
        controleDeArquivo.imprimeBodys(vetorCompressoes, tam[i], nomeDoArquivo,tamDoArquivoEmBytesHuffman);
        controleDeArquivo.imprimeSaida("Huffman", tam[i], tempoHuffman,tamDoArquivoEmBytesHuffman);

        /*******
        * LZ77 *
        *******/

        //comprime
        cout << "Comprimindo com LZ77" << endl;

        LZ77 *lz77 = new LZ77();
        list<Tripla> lista;
        start = clock();
        long long unsigned tamDoArquivoEmBytesLZ77 = 0;
        for (int j = 0; j < tam[i]; j++)
        {
            vetorCompressoes[j] = '\n';

            lista = lz77->codifica(vetorQuestoes[j]);

            for (std::list<Tripla>::iterator it = lista.begin(); it!=lista.end(); ++it)
            {

                vetorCompressoes[j] += '<';
                vetorCompressoes[j] += to_string(it->jump);
                vetorCompressoes[j] += ',';
                vetorCompressoes[j] += to_string(it->size);
                vetorCompressoes[j] += ',';
                vetorCompressoes[j] += it->c;
                vetorCompressoes[j] += '>';
            }
            tamDoArquivoEmBytesLZ77 += lista.size()*(4+4+1);

            //cout <<lista.size()<< endl;
        }
        fim = clock();
        tempoLZ77 = 1000*(fim - start)/(CLOCKS_PER_SEC);
        delete lz77;
        //salva em disco
        nomeDoArquivo = "LZ77" + descricao[i];
        cout << "Imprimindo bodys em " + nomeDoArquivo << endl;
        controleDeArquivo.imprimeBodys(vetorCompressoes, tam[i], nomeDoArquivo,tamDoArquivoEmBytesLZ77);
        controleDeArquivo.imprimeSaida("LZ77", tam[i], tempoLZ77,tamDoArquivoEmBytesLZ77);
        /*******
        * LZ78 *
        *******/

        //comprime
        cout << "Comprimindo com LZ78" << endl;

        LZ78 *lz78 = new LZ78();
        start = clock();
        list<DuplaLZ78> listaLZ78;
        long long unsigned tamDoArquivoEmBytesLZ78 = 0;
        for (int j = 0; j < tam[i]; j++)
        {
            listaLZ78 = lz78->compressao(vetorQuestoes[j]);
            int numCaracter = 0;
            for (std::list<DuplaLZ78>::iterator it = listaLZ78.begin(); it!=listaLZ78.end(); ++it)
            {

                vetorCompressoes[j] += '<';
                vetorCompressoes[j] += to_string(it->num);
                vetorCompressoes[j] += ',';
                vetorCompressoes[j] += it->chave;
                vetorCompressoes[j] += '>';
                numCaracter += it->chave.size();
            }
            tamDoArquivoEmBytesLZ78 += listaLZ78.size()*4+numCaracter;
            //cout<<"LZ78: " << vetorCompressoes[j] <<endl;
        }
        fim = clock();
        tempoLZ78 = 1000*(fim - start)/(CLOCKS_PER_SEC);
        delete lz78;
        //salva em disco
        nomeDoArquivo = "LZ78" + descricao[i];
        cout << "Imprimindo bodys em " + nomeDoArquivo << endl;
        controleDeArquivo.imprimeBodys(vetorCompressoes, tam[i], nomeDoArquivo,tamDoArquivoEmBytesLZ78);
        controleDeArquivo.imprimeSaida("LZ78", tam[i], tempoLZ78,tamDoArquivoEmBytesLZ78);

        /******
        * LZW *
        ******/
        //CORRIGIR O BUG DO LOOP INFINITO E DESCOMENTAR AQUI PARA RODAR LZW
        cout << "Comprimindo com LZW" << endl;

        LZW *lzw = new LZW();
        long long unsigned tamanhoEmBytesDaLZW = 0;
        start = clock();
        for (int j = 0; j < tam[i]; j++)
        {
            vector<int> comprimido;
            //cout << "ENTROU EM COMPRESSAO LZW" << endl;
            comprimido = lzw->compressao(vetorQuestoes[j], comprimido);
            tamanhoEmBytesDaLZW +=  comprimido.size();
            //cout << "SAIU DA COMPRESSAO LZW" << endl;
            vetorCompressoes[j] = '\n';
            //int cont = 0;
            //cout << "ENTROU EM FOR LZW" << endl;
            for (std::vector<int>::iterator k = comprimido.begin(); k!=comprimido.end(); k++)//itera sobre o vetor de inteiro
            {
                //cout << "Contador: " << cont << " | Codigo:" << k.operator*() << endl;
                vetorCompressoes[j] += to_string(k.operator*()) + ", "; // transforma inteiro no indice i em string
                //cont++;
            }
            //cout << "SAIU DO FOR LZW" << endl;

        }
        fim = clock();
        tempoLZW = 1000*(fim - start)/(CLOCKS_PER_SEC);
        //delete lzw;
        //salva em disco
        nomeDoArquivo = "LZW" + descricao[i];
        cout << "Imprimindo bodys em " + nomeDoArquivo << endl;
        controleDeArquivo.imprimeBodys(vetorCompressoes, tam[i], nomeDoArquivo,tamanhoEmBytesDaLZW);

        delete [] vetorQuestoes;
        delete [] vetorCompressoes;

        //imprimir arquivo "saida.txt" com as estatísticas de tempo
        controleDeArquivo.imprimeSaida("LZW", tam[i], tempoLZW,tamanhoEmBytesDaLZW);

    }

    return 0;
}

/**********
 * TESTES *
 **********/


/*
#include <bits/stdc++.h>
#include "LZ77.h"

using namespace std;

int main()
{
    /*****************
     * TESTE HUFFMAN *
     *****************/
/*
ArvHuffman *arv = new ArvHuffman();

string valor = "banaca bacana";
string resultadoCompressao = arv->retornaStringComprimida(valor);
string resultadoDescompressao = arv->descomprime();
cout << "Valor: " << valor << endl;
cout << "Compressao: " << resultadoCompressao << endl;
cout << "Descompressao: " << resultadoDescompressao << endl;
delete arv;
 */

/*************
 * TESTE LZW *
 *************/
/*
   auto *arv = new LZW();//constroi a classe com os algoritmo;

   std::vector<int> comprimido;//vetor de inteiros para dados comprimidos

   std::string dado;
   //dado = "SEROUNAOSERSEROUNAOSER"; //EXEMPLO 1
   dado = "banaca bacana"; //EXEMPLO 2

   cout << "String a ser comprimida|descomprimida: " << dado << endl;
   comprimido = arv->compressao(dado, comprimido);//chama o algoritmo de compressao
   cout << "Codigo de compressao: ";
   copy(comprimido.begin(), comprimido.end(), std::ostream_iterator<int>(std::cout, ", "));//imprime a compressao
   std::cout << std::endl;

   cout << "Descompressao: ";
   std::string decomprimido = arv->descompressao(comprimido.begin(), comprimido.end());//chama o algoritmo de descompressao
   std::cout << decomprimido << std::endl;//imprime string
*/

/**************
* TESTE LZ-78 *
***************/
/*
    auto *arv = new LZ78();
    std::string dado, resultado;
    dado = "SEROUNAOSERSEROUNAOSER"; //EXEMPLO 1
    //dado = "banaca bacana"; //EXEMPLO 2

    cout << "String a ser comprimida|descomprimida: " << dado << endl;
    resultado = arv->compressao(dado);//chama o algoritmo de compressao
    cout << "Codigo de compressao: ";
    cout << resultado;//imprime a compressao
    std::cout << std::endl;

    cout << "Descompressao: ";
    std::string decomprimido = arv->descompressao(resultado);//chama o algoritmo de descompressao
    std::cout << decomprimido << std::endl;//imprime string
*/

/**************
* TESTE LZ-77 *
***************/
/*
    cout << "String para compressao:" << endl;
    string st = "BANANABACANA";
    //string st = "bananabanabofana";
    //string st = "aaaaaaaaaaaaaaaaaaaaaa";
    cout << st << endl;
    cout << "Codigo compressao:" << endl;

    auto *lz = new LZ77();
    list<Tripla> lista;
    lista = lz->codifica(st);

    //CRIADA A LISTA INICIO DO CÓDIGO QUE TRANSFORMA UMA LISTA DE TRIPLAS EM STRING "strString"
    string strSaida = "";
    for (std::list<Tripla>::iterator it = lista.begin(); it!=lista.end(); ++it)
    {
        strSaida += '<';
        strSaida += to_string(it->jump);
        strSaida += ',';
        strSaida += to_string(it->size);
        strSaida += ',';
        strSaida += it->c;
        strSaida += '>';
    }
    //FIM DO CÓDIGO QUE CONCATENA AS TRIPLAS NA STRING "strSaida"

    cout << strSaida;
    delete lz;
*/

/*
    return 0;
}*/