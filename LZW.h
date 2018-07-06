#ifndef ED2_PARTE3_FINAL_LZW_H
#define ED2_PARTE3_FINAL_LZW_H

#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>

class LZW
{
public:
    LZW();
    std::vector<int> compressao(const std::string &naoComprimido, std::vector<int> resultado);
    std::string descompressao(std::vector<int>::iterator inicio, std::vector<int>::iterator fim);
    virtual ~LZW();
};

#endif //ED2_PARTE3_FINAL_LZW_H
