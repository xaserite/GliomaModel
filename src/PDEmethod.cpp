#include "PDEmethod.h"

void PDEmethod::set_methodParameters(methodParameters P){
    N_timeSteps = P.N_timeSteps();
    N_x = P.N_xPoints();
    T = P.T();
    x_0 = P.x_0();
    x_N = P.x_N();
    dt = T/N_timeSteps;
    compute_dx();
}

void PDEmethod::compute_dx(){
    dx = (x_N-x_0)/(N_x-1);
    compute_alpha();
    compute_beta();
}

void PDEmethod::compute_dt(){
    dt = T/N_timeSteps;
    compute_alpha();
    compute_beta();
}

void PDEmethod::compute_alpha(){
    alpha = dt/dx;
}

void PDEmethod::compute_beta(){
    beta = alpha/dx;
}
