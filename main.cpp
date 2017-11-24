#include "DMRG.h"
#include "test.h"


int Sub::nmax;

int main(void)
{
        Parameter para;
        Sub::nmax=para.nmax();
        DMRG haha(para);
        //test(para);
}