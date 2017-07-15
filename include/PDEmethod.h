#ifndef PDEMETHOD_H
#define PDEMETHOD_H

#include <methodParams.h>
#include <fstream>

using namespace std;

class PDEmethod
{
    public:
        PDEmethod();
        virtual ~PDEmethod();

        unsigned int get_timeStep() { return timeStep; }
        double get_T() { return T; }
        void set_T(double val){
            T = val;
            compute_dt();
        }
        unsigned int get_N_timeSteps() { return N_timeSteps; }
        void set_N_timeSteps(unsigned int val){
            N_timeSteps = val;
            compute_dt();
        }
        unsigned int get_N_spatialPoints() { return N_spatialPoints; }
        void set_N_spatialPoints(unsigned int val){
             N_spatialPoints = val;
             compute_dx();
        }
        double get_dt() { return dt; }
        double get_dx() { return dx; }
        void set_methodParameters(methodParameters P);

    protected:
        unsigned int timeStep, N_timeSteps, N_spatialPoints;
        double T, dt, dx, alpha, beta;
        double x_0, x_N;
        ifstream INPUTSTREAM;

    private:
        void compute_dx();
        void compute_dt();
        void compute_alpha();
        void compute_beta();
};

#endif // PDEMETHOD_H
