#include "Rand.h"
#include <cstdlib>

int rand_weight()
{
    int nr;
    nr = rand()%51 + 50;
    return nr;
}

int rand_debt()
{
    int nr;
    nr = rand()%90001 +10000;
    return nr;
}

bool rand_ok()
{
    int nr;
    nr = rand()%2 + 1;
    if(nr==1)
        return true;
    else
        return false;
}

int random()
{
    int nr;
    nr = rand()%100 + 1;
    return nr;
}

int rand_genken()
{
    int nr;
    nr = rand()%3 + 1;
    return nr;
}
