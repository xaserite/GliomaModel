#include "GliomaModel.h"

GliomaModel::GliomaModel(methodParameters P,velocitySpace *v){
    init(P,v);
}

GliomaModel::GliomaModel(methodParameters P,velocitySpace *v,initialValueGen* iV){
    init(P,v);
    set_rho_init(iV->get_rho());
}

GliomaModel::~GliomaModel(){
    rho.clear();
    rho_work.clear();
    rho_init.clear();
    for(size_t i=0;i<V->N();i++){
        g[i].clear();
        g_work[i].clear();
    }
    g.clear();
    g_work.clear();
    vDg.clear();
}

void GliomaModel::compute(){
    timeStep = 0;
    init_values();
    while(timeStep<N_timeSteps){
        swap_func_pointers();
        compute_time_iteration();
        timeStep++;
    }
}

void GliomaModel::init(methodParameters P,velocitySpace *v){
    set_methodParameters(P);
    eps = P.eps();
    l1 = P.l1(); l2 = P.l2();
    V = v;
    rho = vector<double>(N_spatialPoints);
    rho_init = vector<double>(N_spatialPoints);
    rho_work = vector<double>(N_spatialPoints);
    g = vector< vector<double> >(V->N());
    g_work = vector< vector<double> >(V->N());
    vDg = vector<double>(V->N());
    for(size_t j=0;j<V->N();j++){
        g[j] = vector<double>(N_spatialPoints+1);
        g_work[j] = vector<double>(N_spatialPoints+1);
    }
}

void GliomaModel::set_rho_init(vector<double> *data){
    for(size_t i=0;i<N_spatialPoints;i++)
        rho_init[i] = (*data)[i];
}

void GliomaModel::init_values(){
    for(size_t i=0;i<N_spatialPoints;i++){
        rho[i] = rho_work[i] = rho_init[i];
        for(size_t j=0;j<V->N();j++)
            g[j][i] = g_work[j][i] = 0;
    }
}

void GliomaModel::swap_func_pointers(){
    if(timeStep%2==1){
        rho_old = &rho_work;
        rho_up = &rho;
        g_old = &g_work;
        g_up = &g;
    }else{
        rho_old = &rho;
        rho_up = &rho_work;
        g_old = &g;
        g_up = &g_work;
    }
}

void GliomaModel::compute_time_iteration(){
    for(size_t i=1;i<N_spatialPoints;i++)
        compute_g_inner(i);
    for(size_t i=1;i<N_spatialPoints-1;i++)
        compute_rho_inner(i);
    compute_boundary_Neumann();
}

void GliomaModel::compute_vDg_fb(unsigned int i){
    for(size_t j=0;j<V->N();j++)
        if(V->v(j)>0)
            vDg[j] = V->v(j)/dx* ( (*g_old)[j][i]-(*g_old)[j][i-1] );
        else
            vDg[j] = V->v(j)/dx* ( (*g_old)[j][i+1]-(*g_old)[j][i] );
}

void GliomaModel::compute_vDg(unsigned int i){
    for(size_t j=0;j<V->N();j++)
        vDg[j] = V->v(j)*( (*g_up)[j][i+1]-(*g_up)[j][i] )/dx;
}

void GliomaModel::compute_g_inner(unsigned int i){
    compute_vDg_fb(i);
    double vDgInt = integral_vDg();
    double Drho = ( (*rho_old)[i]-(*rho_old)[i-1] )/dx;
    vgInt = integral_vg(i);
    for(size_t j=0;j<V->N();j++){
        double vEDrho = V->v(j)*V->E(j,i) *Drho/eps;
        double ProjvDg = vDg[j] -V->E(j,i)*vDgInt;
        double g_ = (*g_old)[j][i] +dt/eps *( ProjS(i,j)-ProjvDg-vEDrho );
        (*g_up)[j][i] = g_ / (1 + l1* dt/eps/eps);
    }
}

void GliomaModel::compute_rho_inner(unsigned int i){
    compute_vDg(i);
    double vDgInt = integral_vDg();
    double SInt = 0;
    (*rho_up)[i] = (*rho_old)[i] + dt* (SInt - vDgInt);
}

double GliomaModel::ProjS(unsigned int i,unsigned int j){
    double vRhoE = V->v(j)*V->E(j,i)/(2*eps) * ( (*rho_old)[i]+(*rho_old)[i+1] );
    double vgProj = V->v(j)*(*g_old)[j][i] - vgInt*V->E(j,i);
    return l2*(vRhoE + vgProj) ;
}

void GliomaModel::compute_boundary_Neumann(){
    (*rho_up)[0] = (*rho_up)[1];
    (*rho_up)[N_spatialPoints-1] = (*rho_up)[N_spatialPoints-2];
    for(size_t j=0;j<V->N();j++){
        (*g_up)[j][0] = (*g_up)[j][1];
        (*g_up)[j][N_spatialPoints] = (*g_up)[j][N_spatialPoints-1];
    }
}

void GliomaModel::compute_boundary_periodic(){
    (*rho_up)[0] = (*rho_up)[N_spatialPoints-2];
    (*rho_up)[N_spatialPoints-1] = (*rho_up)[1];
    for(size_t j=0;j<V->N();j++){
        (*g_up)[j][0] = (*g_up)[j][N_spatialPoints-1];
        (*g_up)[j][N_spatialPoints] = (*g_up)[j][1];
    }
}

void GliomaModel::compute_boundary_Dirichlet(){
    (*rho_up)[0] = 0;
    (*rho_up)[N_spatialPoints-1] = 0;
    for(size_t j=0;j<V->N();j++){
        (*g_up)[j][0] = 0;
        (*g_up)[j][N_spatialPoints] = 0;
    }
}

double GliomaModel::integral_vDg(){
    double I = 0;
    for(size_t j=0;j<V->N();j++)
        I += vDg[j] * V->w(j);
    return I;
}

double GliomaModel::integral_vg(unsigned int i){
    double I = 0;
    for(size_t j=0;j<V->N();j++)
        I += (*g_old)[j][i] * V->v(j)*V->w(j);
    return I;
}

void GliomaModel::write_toGnuplot(string filename){
    OUTPUTSTREAM.open(filename,ios::out);
    ofstream foo("g_correct.data",ios::out);
    if(!OUTPUTSTREAM) return;
    for(size_t i=0;i<N_spatialPoints;i++){
        OUTPUTSTREAM << x_0+i*dx << "\t" << (*rho_up)[i] << endl;
    }
    for(size_t i=0;i<N_spatialPoints+1;i++)
        foo << x_0+(i-.5)*dx << "\t" << (*g_up)[0][i] << "\t" << (*g_up)[1][i] << endl;
    foo.close();
    OUTPUTSTREAM.close();
}
