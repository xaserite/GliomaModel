#include "GliomaModel.h"
#include <cmath>

GliomaModel::GliomaModel(methodParameters P,velocitySpace *v){
    init(P,v);
}

GliomaModel::GliomaModel(methodParameters P,velocitySpace *v,initialValueGen* iV){
    init(P,v);
    set_rho_init(iV->get_rho());
}

GliomaModel::~GliomaModel(){
    l2.clear();
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
    vgInt.clear();
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
    V = v;
    eps = P.eps();
    l1 = P.l1();
    l2 = vector<double>(dim,P.l2());
    rho = vector<double>(N_x*N_y);
    rho_init = vector<double>(N_x*N_y);
    rho_work = vector<double>(N_x*N_y);
    g = vector< vector<double> >(V->N());
    g_work = vector< vector<double> >(V->N());
    vDg = vector<double>(V->N());
    vgInt = vector<double>(dim);
    for(size_t j=0;j<V->N();j++){
        g[j] = vector<double>( (N_x+1)*(N_y+1) );
        g_work[j] = vector<double>( (N_x+1)*(N_y+1) );
    }
}

void GliomaModel::set_rho_init(vector<double> *data){
    for(size_t i=0;i<N_x;i++)
        for(size_t j=0;j<N_y;j++)
            rho_init[i+N_x*j] = (*data)[i+N_x*j];
}

void GliomaModel::init_values(){
    for(size_t i=0;i<N_x*N_y;i++){
        rho[i] = rho_work[i] = rho_init[i];
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
    if(N_y>1){
        for(size_t i=1;i<N_x;i++)
            for(size_t j=1;j<N_y;j++)
                compute_g_inner(i,j);
        for(size_t i=1;i<N_x-1;i++)
            for(size_t j=1;j<N_y-1;j++)
                compute_rho_inner(i,j);
    }else{
        for(size_t i=1;i<N_x;i++)
            compute_g_inner(i,0);
        for(size_t i=1;i<N_x-1;i++)
            compute_rho_inner(i,0);
    }
    compute_boundary_Neumann();
}

void GliomaModel::compute_g_inner(unsigned int i,unsigned int j){
    compute_vDg_upwind(i,j);
    double vDgInt = integral_vDg();
    compute_vgInt(i,j); // computed here, used in ProjS(.,.,k)
    for(size_t k=0;k<V->N();k++){
        double ProjvDg = vDg[k] -V->E(k,i,j)*vDgInt;
        double g_ = (*g_old)[k][j*(N_x+1) +i] +dt/eps *( ProjS(i,j,k) -ProjvDg -DvrhoE(i,j,k)/eps );
        (*g_up)[k][j*(N_x+1) +i] = g_ / (1 + l1* dt/eps/eps);
    }
}

void GliomaModel::compute_rho_inner(unsigned int i,unsigned int j){ //should be correct
    compute_vDg_center(i,j);
    double vDgInt = integral_vDg();
    double SInt = 0;
    (*rho_up)[j*N_x +i] = (*rho_old)[j*N_x +i] + dt* (SInt - vDgInt);
}

void GliomaModel::compute_vDg_upwind(unsigned int i,unsigned j){
    for(size_t k=0;k<V->N();k++){
        if(V->v(k,0)>0)
            vDg[k] = V->v(k,0)/dx* ( (*g_old)[k][j*(N_x+1) +i]-(*g_old)[k][j*(N_x+1) +i-1] );
        else
            vDg[k] = V->v(k,0)/dx* ( (*g_old)[k][j*(N_x+1) +i+1]-(*g_old)[k][j*(N_x+1) +i] );
        if(dim!=2) continue;
        if(V->v(k,1)>0)
            vDg[k]+= V->v(k,1)/dy* ( (*g_old)[k][j*(N_x+1) +i]-(*g_old)[k][(j-1)*(N_x+1) +i] );
        else
            vDg[k]+= V->v(k,1)/dy* ( (*g_old)[k][(j+1)*(N_x+1) +i]-(*g_old)[k][j*(N_x+1) +i] );
    }
}

void GliomaModel::compute_vDg_center(unsigned int i,unsigned int j){
    if(dim==1)
        for(size_t k=0;k<V->N();k++)
            vDg[k] = V->v(k,0)*( (*g_up)[k][j*(N_x+1) +i+1]-(*g_up)[k][j*(N_x+1) +i] )/dx;
    if(dim==2)
        for(size_t k=0;k<V->N();k++)
            vDg[k]= V->v(k,0)*.5*( (*g_up)[k][j*(N_x+1) +i+1]-(*g_up)[k][j*(N_x+1) +i]
                               +(*g_up)[k][(j+1)*(N_x+1) +i+1]-(*g_up)[k][(j+1)*(N_x+1) +i] )/dx
             + V->v(k,1)*.5*( (*g_up)[k][(j+1)*(N_x+1) +i]-(*g_up)[k][j*(N_x+1) +i]
                             +(*g_up)[k][(j+1)*(N_x+1) +i+1]-(*g_up)[k][j*(N_x+1) +i+1])/dy;

}

double GliomaModel::DvrhoE(unsigned int i,unsigned int j,unsigned int k){
    double D;
    if(dim==1)
        D = V->v(k,0)/dx *( (*rho_old)[j*N_x +i]*V->E(k,i,j) -(*rho_old)[j*N_x +i-1]*V->E(k,i-1,j) );
    if(dim==2)
        D = V->v(k,0)/dx*.5 *( (*rho_old)[j*N_x +i]*V->E(k,i,j) -(*rho_old)[j*N_x +i-1]*V->E(k,i-1,j)
                              +(*rho_old)[(j-1)*N_x +i]*V->E(k,i,j-1) -(*rho_old)[(j-1)*N_x +i-1]*V->E(k,i-1,j-1))
            +V->v(k,1)/dy*.5 *( (*rho_old)[j*N_x +i]*V->E(k,i,j) -(*rho_old)[(j-1)*N_x +i]*V->E(k,i,j-1)
                               +(*rho_old)[j*N_x +i-1]*V->E(k,i-1,j) -(*rho_old)[(j-1)*N_x +i-1]*V->E(k,i-1,j-1) );
    return D;
}

double GliomaModel::ProjS(unsigned int i,unsigned int j,unsigned int k){
    double projS = 0;
    double rE = rhoE(i,j,k)/eps;
    for(size_t d=0;d<dim;d++){
        double vRhoE = V->v(k,d)*rE;
        double vgProj = V->v(k,d)*(*g_old)[k][j*(N_x+1) +i] - vgInt[d]*V->E(k,i,j);
        projS+= l2[d]*(vRhoE + vgProj) ;
    }
    return projS;
}

double GliomaModel::rhoE(unsigned int i,unsigned int j,unsigned int k){
    double rE = (*rho_old)[j*N_x +i]*V->E(k,i,j) +(*rho_old)[j*N_x +i-1]*V->E(k,i-1,j);
    if(dim==1) return rE/2;
    if(dim==2)
        rE += (*rho_old)[(j-1)*N_x +i]*V->E(k,i,j-1) +(*rho_old)[(j-1)*N_x +i-1]*V->E(k,i-1,j-1);
    return rE/4;
}

void GliomaModel::compute_boundary_Neumann(){
    for(size_t j=0;j<N_y;j++){
        (*rho_up)[j*N_x +0] = (*rho_up)[j*N_x +1];
        (*rho_up)[j*N_x +N_x-1] = (*rho_up)[j*N_x +N_x-2];
        for(size_t k=0;k<V->N();k++){
            (*g_up)[k][j*(N_x+1) +0] = (*g_up)[k][j*(N_x+1) +1];
            (*g_up)[k][j*(N_x+1) +N_x] = (*g_up)[k][j*(N_x+1) +N_x-1];
        }
    }
    if(dim!=2) return;
    for(size_t i=0;i<N_x;i++){
        (*rho_up)[i] = (*rho_up)[N_x+i];
        (*rho_up)[(N_y-1)*N_x +i] = (*rho_up)[(N_y-2)*N_x +i];
        for(size_t k=0;k<V->N();k++){
            (*g_up)[k][i] = (*g_up)[k][N_y+1 +i];
            (*g_up)[k][N_y*(N_x+1) +i] = (*g_up)[k][(N_y-1)*(N_x+1) +i];
        }
    }
}

void GliomaModel::compute_boundary_periodic(){
    (*rho_up)[0] = (*rho_up)[N_x-2];
    (*rho_up)[N_x-1] = (*rho_up)[1];
    for(size_t j=0;j<V->N();j++){
        (*g_up)[j][0] = (*g_up)[j][N_x-1];
        (*g_up)[j][N_x] = (*g_up)[j][1];
    }
}

void GliomaModel::compute_boundary_Dirichlet(){
    (*rho_up)[0] = 0;
    (*rho_up)[N_x-1] = 0;
    for(size_t j=0;j<V->N();j++){
        (*g_up)[j][0] = 0;
        (*g_up)[j][N_x] = 0;
    }
}

double GliomaModel::integral_vDg(){
    double I = 0;
    for(size_t k=0;k<V->N();k++)
        I += vDg[k] * V->w(k);
    return I;
}

void GliomaModel::compute_vgInt(unsigned int i,unsigned int j){
    for(size_t d=0;d<dim;d++){
        vgInt[d] = 0;
        for(size_t k=0;k<V->N();k++)
            vgInt[d] += (*g_old)[k][j*(N_x+1) +i] * V->v(k,d)*V->w(k);
    }
}

void GliomaModel::write_toGnuplot(string filename){
    OUTPUTfILESTREAM.open(filename,ios::out);
    if(!OUTPUTfILESTREAM) return;
    if(dim==1){
        for(size_t i=0;i<N_x;i++)
            OUTPUTfILESTREAM << x_0+i*dx << "\t" << (*rho_up)[i] << endl;
    }else if(dim==2)
        for(size_t i=0;i<N_x;i++){
            for(size_t j=0;j<N_y;j++)
                OUTPUTfILESTREAM << x_0+i*dx << "\t" << y_0+j*dy << "\t" << (*rho_up)[j*N_x+i] << endl;
            OUTPUTfILESTREAM << endl;
        }
    OUTPUTfILESTREAM.close();
}
