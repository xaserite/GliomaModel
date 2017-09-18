#include "PDEmethod.h"

void PDEmethod::set_methodParameters(methodParameters P){
    dim = P.Dim();
    N_timeSteps = P.N_timeSteps();
    N_x = P.N_xPoints();
    N_y = P.N_yPoints();
    T = P.T();
    x_0 = P.x_0();
    x_N = P.x_N();
    y_0 = P.y_0();
    y_N = P.y_N();
    dt = T/N_timeSteps;
    compute_dx();
    if(dim==2) compute_dy();
}

void PDEmethod::compute_dx(){
    dx = (x_N-x_0)/(N_x-1);
    compute_alpha_x();
    compute_beta_x();
}

void PDEmethod::compute_dy(){
    dy = (y_N-y_0)/(N_y-1);
    compute_alpha_y();
    compute_beta_y();
}

void PDEmethod::compute_dt(){
    dt = T/N_timeSteps;
    compute_alpha_x();
    compute_beta_x();
    compute_alpha_y();
    compute_beta_y();
}

void PDEmethod::compute_alpha_x(){
    alpha_x = dt/dx;
}

void PDEmethod::compute_beta_x(){
    beta_x = alpha_x/dx;
}

void PDEmethod::compute_alpha_y(){
    alpha_y = dt/dx;
}

void PDEmethod::compute_beta_y(){
    beta_y = alpha_y/dx;
}
