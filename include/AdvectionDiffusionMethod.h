#ifndef ADVECTIONDIFFUSIONMETHOD_H
#define ADVECTIONDIFFUSIONMETHOD_H

#include <PDEmethod.h>
#include <methodParams.h>
#include <initialValueGen.h>
#include <velocitySpace.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class AdvectionDiffusionMethod : public PDEmethod
{
    public:
        AdvectionDiffusionMethod() {}
        AdvectionDiffusionMethod(methodParameters P,velocitySpace *v, initialValueGen* iV);
        ~AdvectionDiffusionMethod(){
            rho.clear();
            rho_work.clear();
            rho_init.clear();
            vvQint.clear();
        }

        void compute();
        void read_initialValues(string filename);
        void set_initialValues(vector<double> data);
        void set_initialValues(vector<double> *data);
        void write_toGnuplot(string filename);

    protected:

    private:
        vector<double> rho, rho_work, rho_init, vvQint;
        double l1, l2;
        velocitySpace *V;

        void init_values();
        void compute_vvQint();
        void compute_time_iteration(vector<double>* rho_from, vector<double>* rho_to);
        void compute_boundary_values(vector<double>* rho_from, vector<double>* rho_to);
        void compute_boundary_values_Neumann(vector<double>* rho_to);
        void compute_spatial_point(vector<double>* rho_from, vector<double>* rho_to, size_t i);
};

#endif // ADVECTIONDIFFUSIONMETHOD_H
