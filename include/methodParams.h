#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <fstream>

using namespace std;

class methodParameters{
    public:
        methodParameters(){}
        methodParameters(string filename){
            ifstream INPUTSTREAM;
            INPUTSTREAM.open(filename,ios::in);
            INPUTSTREAM >> n_timeSteps >> n_spatialPoints;
            INPUTSTREAM >> t >> X_0 >> X_N;
            INPUTSTREAM >> Eps;
            INPUTSTREAM.close();
        }
        ~methodParameters(){};
        unsigned int N_timeSteps(){ return n_timeSteps; }
        unsigned int N_spatialPoints(){ return n_spatialPoints; }
        double T(){ return t; }
        double x_0(){ return X_0; }
        double x_N(){ return X_N; }
        double eps(){ return Eps; }
    protected:
    private:
        unsigned int n_timeSteps, n_spatialPoints;
        double t, X_0, X_N, Eps;
};

#endif // PARAMETER_H
