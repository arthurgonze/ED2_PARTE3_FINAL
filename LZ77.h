#ifndef ED2_PARTE3_FINAL_LZ77_H
#define ED2_PARTE3_FINAL_LZ77_H

#include <string>
#include <list>

using namespace std;

struct Tripla
{
    char c;
    int jump;
    int size;
};

class LZ77
{
public:
    list<Tripla> codifica(string st);
};

#endif //ED2_PARTE3_FINAL_LZ77_H
