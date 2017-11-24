#ifndef Q_WAVE_H
#define Q_WAVE_H
#include<vector>
#include "Sub.h"
#include "SingleSub.h"

class QWave
{
private:

        MatrixXd _Wave;//The Wave is Sm En initially.
        const int DSys, DEnv, Dm, Dn;
        //========================reshape===============================
        void Wave2S(MatrixXd& A)const;//sm,en to s, men.
        void S2Wave(const MatrixXd& A);
        void Wave2M(MatrixXd& A)const;//sm,en to m, sen.
        void M2Wave(const MatrixXd& A);
        void Wave2E(MatrixXd& A)const;//sm,en to nsm, e.
        void E2Wave(const MatrixXd& A);
        void Wave2N(MatrixXd& A)const;//sm,en to esm, n.
        void N2Wave(const MatrixXd& A);


public:

        const MatrixXd& Wave()const{return _Wave;};
        //QWave(){};
        ~QWave(){};
        QWave(const QWave&a):
        DSys(a.DSys),
        DEnv(a.DEnv),
        Dm(a.Dm),
        Dn(a.Dn),
        _Wave(a._Wave)
        {};
        QWave(const int& sys, const int& m, const int& n, const int& env):
        DSys(sys),
        DEnv(env),
        Dm(m),
        Dn(n),
        _Wave(MatrixXd::Zero(sys*m, env*n))
        {};

//=================================================================================

        //void SysOPWave(const MatrixXd&);
        void SysOPWave(const MatrixXd&);//S*Wave;
        void EnvOPWave(const MatrixXd&);//Wave*E^T
        void MOPWave(const SpMat&);//M*Wave
        void NOPWave(const SpMat&);//N*Wave

        void Transform();//Transform form SmEn into nSmE
        void TransBack();//Transform form nSmE back SmEn
//=================================================================================
        const MatrixXd& LOPWave(const MatrixXd&);//wave=L*wave
        const MatrixXd& ROPWave(const MatrixXd&);//wave=wave*R
        const MatrixXd& LROPWave(const MatrixXd&, const MatrixXd&);//wave=L*wave*R
//=================================================================================
        void add(const QWave& a){_Wave+=a._Wave;};//wave+=a;
        void time(const double& J){_Wave*=J;};


        const vector<double>& Wave2f(vector<double>& f)const;
        const MatrixXd& f2Wave(const vector<double>& f);
        const MatrixXd& f2Wave(const VectorXd& f);

        const QWave& operator=(const QWave& a)
        {
                _Wave=a.Wave();
                return *this;
        }


        const MatrixXd& TruncL(MatrixXd& truncU, const int& D)const;
        const MatrixXd& TruncR(MatrixXd& truncV, const int& D)const;






};


#endif // Q_WAVE_H
