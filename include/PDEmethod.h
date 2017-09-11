#ifndef PDEMETHOD_H
#define PDEMETHOD_H

#include <methodParams.h>
#include <fstream>

using namespace std;

class PDEmethod
{
    public:
        PDEmethod(){}
        virtual ~PDEmethod(){}

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
        unsigned int get_N_x() { return N_x; }
        void set_N_x(unsigned int val){
             N_x = val;
             compute_dx();
        }
        unsigned int get_N_y() { return N_y; }
        void set_N_y(unsigned int val){
             N_y = val;
             compute_dy();
        }
        double get_dt() { return dt; }
        double get_dx() { return dx; }
        double get_dy() { return dy; }
        void set_methodParameters(methodParameters P);

    protected:
        unsigned int timeStep, N_timeSteps, N_x, N_y;
        double T, dt, dx, dy, alpha, beta;
        double x_0, x_N, y_0, y_N;
        ifstream INPUTSTREAM;
        ofstream OUTPUTSTREAM;

    private:
        void compute_dx();
        void compute_dy();
        void compute_dt();
        void compute_alpha();
        void compute_beta();
};

#endif // PDEMETHOD_H
