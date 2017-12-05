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
        void compute_incomplete();
        void set_rho_init(vector<double> *data);
        void write_toGnuplot(string filename);
        void write_toContol(string filename);
        bool was_monotonicity_preserved();

    private:
        vector<double> rho, rho_work, rho_init, vDg, l2,vgInt;
        vector< vector<double> >  g, g_work;
        vector<double> *rho_old, *rho_up;
        vector< vector<double> > *g_old, *g_up;
        velocitySpace *V;
        double eps, l1, rho_init_max=1;
        ofstream OUTPUTfILESTREAM;
        bool monotonicity_preserved = true;

        void init(methodParameters P,velocitySpace *v);
        void init_values();
        void reset_g();
        void swap_func_pointers();
        void compute_time_iteration();
        void compute_g_inner(unsigned int i,unsigned int j);
        void compute_rho_inner(unsigned int i,unsigned int j);
        void compute_vDg_upwind(unsigned int i,unsigned int j);
        void compute_vDg_center(unsigned int i,unsigned int j);
        void compute_vgInt(unsigned int i,unsigned int j);
        void validate_monotonicity(unsigned int i,unsigned int j);
        void compute_boundary_Neumann();
        void compute_boundary_periodic();
        void compute_boundary_Dirichlet();

        double integral_vDg();
        double rhoE(unsigned int i,unsigned int j,unsigned int k);
        double DvrhoE(unsigned int i,unsigned j,unsigned k);
        double ProjS(unsigned int i,unsigned int j,unsigned int k);
};

#endif // GLIOMAMODEL_H
