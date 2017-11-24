#ifndef DMRG_H
#define DMRG_H
#include "SuperEnergy.h"



class DMRG
{
public:
        Sub Sys;
        Sub Env;
        Sub m;
        Sub n;


        DMRG(){};
        ~DMRG(){};

        DMRG(Parameter& para);
        MatrixXd IniWave;

        void Initialize(const int& dir, const int& Gdir, const int& OS, const int& OE);



        //=================periodic condition==================
        void BuildUp(Parameter& para, int& OS, int& OE);
        
        //================sweep======================
        void Sweep(Parameter& para, int& OS, int& OE);
        void CalcuEnergy(Parameter& para, int& OS,
         int& OE, const int& dir, const int& Gdir);
        //===========one site sweep===================
        void OneSiteSweep(Parameter& para, int& OS, int& OE);
        
        
        
};









#endif // DMRG_H
