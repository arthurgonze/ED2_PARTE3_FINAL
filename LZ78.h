#ifndef ED2_PARTE3_FINAL_LZ78_H
#define ED2_PARTE3_FINAL_LZ78_H
#include <list>
#include <string>

using namespace std;

struct DuplaLZ78
{
    string chave;
    int num;
};

class LZ78
{
public:
    LZ78();
    list<DuplaLZ78> compressao(std::string entrada);
    std::string descompressao(std::string entrada);
    virtual ~LZ78();
};


#endif //ED2_PARTE3_FINAL_LZ78_H
