#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <fstream>
#include <exception>

using namespace std;

class methodParameters{
    public:
        methodParameters(){}
        methodParameters(string filename){
            ifstream INPUTSTREAM;
            INPUTSTREAM.open(filename,ios::in);
            INPUTSTREAM >> dim;
            if(dim!=1 && dim!=2)
                throw "exception: methodParameters requires dim to be 1 or 2";
            INPUTSTREAM >> n_timeSteps >> t;
            INPUTSTREAM >> n_xpoints >> X_0 >> X_N;
            if(dim==2)
                INPUTSTREAM >> n_ypoints >> Y_0 >> Y_N;
            INPUTSTREAM >> L1 >> L2;
            INPUTSTREAM >> Eps;
            INPUTSTREAM.close();
        }
        ~methodParameters(){};
        unsigned int Dim(){ return dim; }
        unsigned int N_timeSteps(){ return n_timeSteps; }
        unsigned int N_xPoints(){ return n_xpoints; }
        unsigned int N_yPoints(){ return n_ypoints; }
        double T(){ return t; }
        double x_0(){ return X_0; }
        double x_N(){ return X_N; }
        double y_0(){ return Y_0; }
        double y_N(){ return Y_N; }
        double eps(){ return Eps; }
        double l1(){ return L1; }
        double l2(){ return L2; }
    protected:
    private:
        unsigned int n_timeSteps, n_xpoints, n_ypoints, dim;
        double t, X_0, X_N, Y_0,Y_N, Eps, L1, L2;
};

#endif // PARAMETER_H
