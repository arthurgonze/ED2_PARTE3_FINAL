#ifndef ED2_PARTE3_FINAL_LZ78_H
#define ED2_PARTE3_FINAL_LZ78_H

#include <string>
class LZ78
{
public:
    LZ78();
    std::string compressao(std::string entrada);
    std::string descompressao(std::string entrada);
    virtual ~LZ78();
};

#endif //ED2_PARTE3_FINAL_LZ78_H
