#ifndef ADVECTIONDIFFUSIONMETHOD_H
#define ADVECTIONDIFFUSIONMETHOD_H

#include <PDEmethod.h>
#include <methodParams.h>
#include <vector>
#include <fstream>

using namespace std;

class AdvectionDiffusionMethod : public PDEmethod
{
    public:
        AdvectionDiffusionMethod() {}
        AdvectionDiffusionMethod(methodParameters P);
        AdvectionDiffusionMethod(methodParameters P,vector<double> data);
        virtual ~AdvectionDiffusionMethod() {}

        void compute();
        void read_initialValues(char* filename);
        void set_initialValues(vector<double> data);

    protected:

    private:
        vector<double> rho, rho_work, rho_init;
        double (*vvQ)(unsigned int);
        void init_values();
        void compute_time_iteration(vector<double>* rho_from, vector<double>* rho_to);
        void compute_boundary_values(vector<double>* rho_from, vector<double>* rho_to);
        void compute_boundary_values_Neumann(vector<double>* rho_to);
        void compute_spatial_point(vector<double>* rho_from, vector<double>* rho_to, size_t i);
};

#endif // ADVECTIONDIFFUSIONMETHOD_H
