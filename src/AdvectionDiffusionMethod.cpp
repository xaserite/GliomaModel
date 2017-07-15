#include "AdvectionDiffusionMethod.h"

AdvectionDiffusionMethod::AdvectionDiffusionMethod(methodParameters P){
    set_methodParameters(P);
    rho = vector<double>(N_spatialPoints);
    rho_init = vector<double>(N_spatialPoints);
    rho_work = vector<double>(N_spatialPoints);
}

AdvectionDiffusionMethod::AdvectionDiffusionMethod(methodParameters P,vector<double> data){
    set_methodParameters(P);
    rho = vector<double>(N_spatialPoints);
    rho_init = vector<double>(N_spatialPoints);
    rho_work = vector<double>(N_spatialPoints);
    if(data.size()==N_spatialPoints) set_initialValues(data);
}

void AdvectionDiffusionMethod::compute(){
    timeStep = 0;
    init_values();
    while(timeStep<N_timeSteps){
        if(timeStep%2) compute_time_iteration(&rho_work,&rho);
        else compute_time_iteration(&rho,&rho_work);
        timeStep++;
    }
}

void AdvectionDiffusionMethod::init_values(){
    for(size_t i=0;i<N_spatialPoints;i++)
        rho[i] = rho_work[i] = rho_init[i];
}

void AdvectionDiffusionMethod::compute_time_iteration(vector<double>* rho_from, vector<double>* rho_to){
    for(size_t i=1;i<N_spatialPoints-1;i++)
        compute_spatial_point(rho_from,rho_to,i);
    compute_boundary_values(rho_from,rho_to);
}

void AdvectionDiffusionMethod::compute_boundary_values(vector<double>* rho_from, vector<double>* rho_to){
    compute_boundary_values_Neumann(rho_to);
}

void AdvectionDiffusionMethod::compute_boundary_values_Neumann(vector<double>* rho_to){
    (*rho_to)[0] = (*rho_to)[1];
    (*rho_to)[N_spatialPoints] = (*rho_to)[N_spatialPoints-1];
}

void AdvectionDiffusionMethod::compute_spatial_point(vector<double>* rho_from, vector<double>* rho_to, size_t i){
    (*rho_to)[i] = (*rho_from)[i]
        + beta*( (*rho_from)[i-1]-2*(*rho_from)[i]+(*rho_from)[i+1] )
        - .5*alpha*( (*rho_from)[i+1]-(*rho_from)[i-1] );
}

void AdvectionDiffusionMethod::read_initialValues(char* filename){
    unsigned int N_x;
    INPUTSTREAM.open(filename,ios::in);
    if(!INPUTSTREAM) return;
    INPUTSTREAM >> N_x;
    if(N_x==N_spatialPoints)
        for(size_t it=0;it<N_x;it++)
            INPUTSTREAM >> rho_init[it];
    INPUTSTREAM.close();
}

void AdvectionDiffusionMethod::set_initialValues(vector<double> data){
    rho_init = data;
}
