#include "SuperEnergy.h"
#include "SingleSub.h"
#include <ctime>
void test(Parameter& para);
void SaveTruncM(const MatrixXd& A, const int& logo);
void ReadTruncM(MatrixXd& A, const int& logo);

void test(Parameter& para)
{
        SingleSub m(para);
        Sub Sys(para, 1);

        Super Sup(para, Sys, Sys);
        MatrixXd IniWave(MatrixXd::Random(100, 100));
        SaveTruncM(IniWave, 1003);

        vector<double> f;
        for(int i=0; i<100; ++i)
        {
            for(int j=0; j<100; ++j)f.push_back(IniWave(i,j));
        }
        Sup._Wave.f2Wave(f);

        Sup.OneIteration();

        
        SaveTruncM(Sup.Wave().Wave(), 1001);

        
        

}