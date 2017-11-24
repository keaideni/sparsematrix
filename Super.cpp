#include "Super.h"

void Super::f1tof2(const vector<double>& f, vector<double>& g)
{
        _Wave.f2Wave(f);
        OneIteration();
        _Wave.Wave2f(g);
}

void Super::OneIteration()
{
        QWave temp(_Wave);
        _Wave.SysOPWave(Sys.System());

        QWave temp1(temp);
        temp1.EnvOPWave(Env.System());
        _Wave.add(temp1);

        temp1=temp;
        temp1.MOPWave(m.System());
        _Wave.add(temp1);

        temp1=temp;
        temp1.NOPWave(n.System());
        _Wave.add(temp1);


//==========Sys-m=====================
        temp1=temp;
        temp1.SysOPWave(Sys.SysA());
        temp1.MOPWave(m.SysAdag());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.SysOPWave(Sys.SysAdag());
        temp1.MOPWave(m.SysA());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.SysOPWave(Sys.SysAdag());
        temp1.MOPWave(m.SysAdag());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.SysOPWave(Sys.SysA());
        temp1.MOPWave(m.SysA());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

//=================m-Env=====================
        temp1=temp;
        temp1.EnvOPWave(Env.SysA1());
        temp1.MOPWave(m.SysAdag());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.EnvOPWave(Env.SysAdag1());
        temp1.MOPWave(m.SysA());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.EnvOPWave(Env.SysAdag1());
        temp1.MOPWave(m.SysAdag());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.EnvOPWave(Env.SysA1());
        temp1.MOPWave(m.SysA());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

//====================Env-n==============================
        temp1=temp;
        temp1.EnvOPWave(Env.SysA());
        temp1.NOPWave(n.SysAdag());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.EnvOPWave(Env.SysAdag());
        temp1.NOPWave(n.SysA());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.EnvOPWave(Env.SysAdag());
        temp1.NOPWave(n.SysAdag());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.EnvOPWave(Env.SysA());
        temp1.NOPWave(n.SysA());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

//=============for the periodic bound condition=====================
        //===========n-Sys=====================
        temp1=temp;
        temp1.SysOPWave(Sys.SysA1());
        temp1.NOPWave(n.SysAdag());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.SysOPWave(Sys.SysAdag1());
        temp1.NOPWave(n.SysA());
        temp1.time(-1*Jr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.SysOPWave(Sys.SysAdag1());
        temp1.NOPWave(n.SysAdag());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);

        temp1=temp;
        temp1.SysOPWave(Sys.SysA1());
        temp1.NOPWave(n.SysA());
        temp1.time(-1*Jcr);
        _Wave.add(temp1);



        
}


void Super::f1tof2(double* f, double* g)
{
        vector<double> ff, gg;
        for(int i=0; i<Dim; ++i)
        {
                ff.push_back(f[i]);
        }
        f1tof2(ff,gg);
        for(int i=0; i<Dim; ++i)
        {
                g[i]=gg.at(i);
        }
}