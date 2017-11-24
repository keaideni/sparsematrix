#include "SuperEnergy.h"
#include "SingleSub.h"
#include <ctime>

void test(Parameter& para);

void test(Parameter& para)
{
        
        MatrixXd System(MatrixXd::Random(1000, 1000));

        SingleSub m(para), n(para);

        //Sys.Read(11);Env.Read(14);

        QWave wave1(1000, m.System().rows(),
         n.System().rows(), 1000);

        //QWave wave2(wave1);

        time_t start, end;
        time(&start);
        wave1.EnvOPWave(System);//cout<<wave1.Wave()(437,500)<<endl;
        time(&end);cout<<end-start<<endl;

        time(&start);
        wave1.MOPWave(m.System());//cout<<wave1.Wave()(437,500)<<endl;
        time(&end);cout<<end-start<<endl;

        time(&start);
        wave1.NOPWave(n.System());//cout<<wave1.Wave()(437,500)<<endl;
        time(&end);cout<<end-start<<endl;
        

}