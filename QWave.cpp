#include "QWave.h"
struct Eigstruct
{
        double lamda;
        VectorXd state;
};



bool comp(const Eigstruct& a, const Eigstruct& b);
bool comp(const Eigstruct& a, const Eigstruct& b)
{
        return (a.lamda > b.lamda);
}
//============================Reshape===================================
void QWave::Wave2S(MatrixXd& A)const
{
        A.resize(DSys, DEnv*Dm*Dn);
        for(int ie=0; ie<DEnv*Dn; ++ie)
        {
                for(int is=0; is<DSys; ++is)
                        {
                                for(int im=0; im<Dm; ++im)
                                {
                                        A(is, im*DEnv*Dn+ie)=_Wave(is*Dm+im, ie);
                                }
                        }
        }
}
void QWave::S2Wave(const MatrixXd& A)
{
        for(int ie=0; ie<DEnv*Dn; ++ie)
        {
                for(int is=0; is<DSys; ++is)
                        {
                                for(int im=0; im<Dm; ++im)
                                {
                                        _Wave(is*Dm+im, ie)=A(is, im*DEnv*Dn+ie);
                                }
                        }
        }
}
void QWave::Wave2M(MatrixXd& A)const
{
        A.resize(Dm, DSys*DEnv*Dn);
        for(int ie=0; ie<DEnv*Dn; ++ie)
        {
                for(int is=0; is<DSys; ++is)
                        {
                                for(int im=0; im<Dm; ++im)
                                {
                                        A(im, is*DEnv*Dn+ie)=_Wave(is*Dm+im, ie);
                                }
                        }
        }
}

void QWave::M2Wave(const MatrixXd& A)
{
        for(int ie=0; ie<DEnv*Dn; ++ie)
        {
                for(int is=0; is<DSys; ++is)
                        {
                                for(int im=0; im<Dm; ++im)
                                {
                                        _Wave(is*Dm+im, ie)=A(im, is*DEnv*Dn+ie);
                                }
                        }
        }
}
void QWave::Wave2E(MatrixXd& A)const
{
        A.resize(Dm*DSys*Dn, DEnv);
        for(int ie=0; ie<DEnv; ++ie)
        {
                for(int in=0; in<Dn; ++in)
                        {
                                for(int is=0; is<Dm*DSys; ++is)
                                {
                                        A(in*DSys*Dm+is, ie)=_Wave(is, ie*Dn+in);
                                }
                        }
        }
}
void QWave::E2Wave(const MatrixXd& A)
{
        for(int ie=0; ie<DEnv; ++ie)
        {
                for(int in=0; in<Dn; ++in)
                        {
                                for(int is=0; is<Dm*DSys; ++is)
                                {
                                        _Wave(is, ie*Dn+in)=A(in*DSys*Dm+is, ie);
                                }
                        }
        }
}
void QWave::Wave2N(MatrixXd& A)const
{
        A.resize(Dm*DSys*DEnv, Dn);
        for(int in=0; in<Dn; ++in)
        {
                for(int ie=0; ie<DEnv; ++ie)
                        {
                                for(int is=0; is<Dm*DSys; ++is)
                                {
                                        A(ie*DSys*Dm+is, in)=_Wave(is, ie*Dn+in);
                                }
                        }
        }
}

void QWave::N2Wave(const MatrixXd& A)
{
        for(int in=0; in<Dn; ++in)
        {
                for(int ie=0; ie<DEnv; ++ie)
                        {
                                for(int is=0; is<Dm*DSys; ++is)
                                {
                                        _Wave(is, ie*Dn+in)=A(ie*DSys*Dm+is, in);
                                }
                        }
        }
}






//=================The Sparse parts used OPWave=========================
/*void QWave::SysOPWave(const MatrixXd& O)
{
        MatrixXd temp(MatrixXd::Zero(_Wave.rows(), _Wave.cols()));
        for(int is=0; is<DSys; ++is)
        {
                for(int ie=0; ie<DEnv; ++ie)
                {
                        for(int in=0; in<Dn; ++in)
                        {
                                for(int iss=0; iss<DSys; ++iss)
                                {
                                        for(int im=0; im<Dm; ++im)
                                        {
                                                temp(is*Dm+im, ie*Dn+in)+=
                                                O(is, iss)*_Wave(iss*Dm+im, ie*Dn+in);
                                        }
                                }
                        }
                }
        }
        _Wave=temp;
}*/
void QWave::SysOPWave(const MatrixXd& O)
{
        MatrixXd temp;
        Wave2S(temp);
        temp=O*temp;
        S2Wave(temp);
}

void QWave::EnvOPWave(const MatrixXd& O)
{
        MatrixXd temp;
        Wave2E(temp);
        temp=temp*O.transpose();
        E2Wave(temp);
}
void QWave::MOPWave(const SpMat& O)
{
        MatrixXd temp;
        Wave2M(temp);
        temp=O*temp;
        M2Wave(temp);
}
void QWave::NOPWave(const SpMat& O)
{
        MatrixXd temp;
        Wave2N(temp);
        temp=temp*O.transpose();
        N2Wave(temp);
}

void QWave::Transform()
{
        MatrixXd temp(_Wave);
        for(int ie=0; ie<DEnv; ++ie)
        {
                for(int im=0; im<Dm; ++im)
                {
                        for(int is=0; is<DSys; ++is)
                        {
                                for(int in=0; in<Dn; ++in)
                                {
                                        _Wave(in*DSys+is, im*DEnv+ie)
                                        =temp(is*Dm+im, ie*Dn+in);
                                }
                        }
                }
        }
}

/*void QWave::TransBack()
{
        MatrixXd temp(_Wave);
        for(int ie=0; ie<DEnv; ++ie)
        {
                for(int im=0; im<Dm; ++im)
                {
                        for(int is=0; is<DSys; ++is)
                        {
                                for(int in=0; in<Dn; ++in)
                                {
                                        _Wave(is*Dm+im, ie*Dn+in)
                                        =temp(in*DSys+is, im*DEnv+ie);
                                }
                        }
                }
        }
}*/







//=================The Dense matrix used OPWave======================
const MatrixXd& QWave::LOPWave(const MatrixXd& sys)
{
        _Wave=sys*_Wave;

        return _Wave;
}

const MatrixXd& QWave::ROPWave(const MatrixXd& Env)
{
        _Wave=_Wave*Env.transpose();

        return _Wave;
}


const MatrixXd& QWave::LROPWave(const MatrixXd& Sys, const MatrixXd& Env)
{
        _Wave=Sys*_Wave*Env.transpose();
        return _Wave;
}
//===========================================================================

const vector<double>& QWave::Wave2f(vector<double>& f)const
{
        for(int i=0; i<_Wave.rows(); ++i)
        {
                for(int j=0; j<_Wave.cols(); ++j)
                {
                        f.push_back(_Wave(i,j));
                }
        }

        return f;
}


const MatrixXd& QWave::f2Wave(const vector<double>& f)
{
        for(int i=0; i<_Wave.rows(); ++i)
        {
                for(int j=0; j<_Wave.cols(); ++j)
                {
                        _Wave(i, j)=f.at(i*_Wave.cols()+j);
                }
        }

        return _Wave;
}


const MatrixXd& QWave::f2Wave(const VectorXd& f)
{
        for(int i=0; i<_Wave.rows(); ++i)
        {
                for(int j=0; j<_Wave.cols(); ++j)
                {
                        _Wave(i, j)=f(i*_Wave.cols()+j);
                }
        }

        return _Wave;
}




const MatrixXd& QWave::TruncL(MatrixXd& truncU, const int& D)const
{
        vector<Eigstruct> denmat;

        if(_Wave.cols()*_Wave.rows()>16)
        {
                BDCSVD<MatrixXd> svd(_Wave, ComputeFullU);
                for(int i=0; i<svd.singularValues().rows(); ++i)
                {
                        Eigstruct base;
                        base.lamda=svd.singularValues()(i);
                        base.state=svd.matrixU().col(i);

                        denmat.push_back(base);
                }
        }else
        {
                JacobiSVD<MatrixXd> svd(_Wave, ComputeFullU);
                for(int i=0; i<svd.singularValues().rows(); ++i)
                {
                        Eigstruct base;
                        base.lamda=svd.singularValues()(i);
                        base.state=svd.matrixU().col(i);

                        denmat.push_back(base);
                }
        }

        sort(denmat.begin(), denmat.end(), comp);

        int nrow(_Wave.rows());
        int ncol(D<denmat.size()?D:denmat.size());
        truncU=MatrixXd::Zero(nrow, ncol);

        for(int i=0; i<ncol; ++i)
        {
                truncU.col(i)=denmat.at(i).state;
        }

        return truncU;

}
const MatrixXd& QWave::TruncR(MatrixXd& truncV, const int& D)const
{
        vector<Eigstruct> denmat;

        if(_Wave.cols()*_Wave.rows()>16)
        {
                BDCSVD<MatrixXd> svd(_Wave, ComputeFullV);
                for(int i=0; i<svd.singularValues().rows(); ++i)
                {
                        Eigstruct base;
                        base.lamda=svd.singularValues()(i);
                        base.state=svd.matrixV().col(i);

                        denmat.push_back(base);
                }
        }else
        {
                JacobiSVD<MatrixXd> svd(_Wave, ComputeFullV);
                for(int i=0; i<svd.singularValues().rows(); ++i)
                {
                        Eigstruct base;
                        base.lamda=svd.singularValues()(i);
                        base.state=svd.matrixV().col(i);

                        denmat.push_back(base);
                }
        }

        sort(denmat.begin(), denmat.end(), comp);

        int nrow(_Wave.cols());
        int ncol(D<denmat.size()?D:denmat.size());
        truncV=MatrixXd::Zero(nrow, ncol);

        for(int i=0; i<ncol; ++i)
        {
                truncV.col(i)=denmat.at(i).state;
        }

        return truncV;
}