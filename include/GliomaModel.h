#ifndef GLIOMAMODEL_H
#define GLIOMAMODEL_H

#include <initialValueGen.h>
#include <PDEmethod.h>
#include <methodParams.h>
#include <velocitySpace.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class GliomaModel : public PDEmethod
{
    public:
        GliomaModel(){}
        GliomaModel(methodParameters P,velocitySpace *V);
        GliomaModel(methodParameters P,velocitySpace *V,initialValueGen* iV);
        ~GliomaModel();

        void compute();
        void set_rho_init(vector<double> *data);
        void write_toGnuplot(string filename);

    private:
        vector<double> rho, rho_work, rho_init, vDg;
        vector< vector<double> >  g, g_work;
        vector<double> *rho_old, *rho_up;
        vector< vector<double> > *g_old, *g_up;
        velocitySpace *V;
        double eps, l1, l2;
        double vgInt;
        ofstream OUTPUTfILESTREAM;

        void init_values();
        void swap_func_pointers();
        void compute_time_iteration();
        void compute_vDg_fb(unsigned int i);
        void compute_vDg(unsigned int i);
        void compute_g_inner(unsigned int i);
        void compute_rho_inner(unsigned int i);
        void compute_boundary_Neumann();
        void compute_boundary_periodic();
        void compute_boundary_Dirichlet();

        double integral_vDg();
        double integral_vg(unsigned int i);
        double ProjS(unsigned int i,unsigned int j);
};

#endif // GLIOMAMODEL_H
