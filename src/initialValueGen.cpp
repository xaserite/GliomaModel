#include "initialValueGen.h"

initialValueGen::initialValueGen(unsigned int n, string mode,string method){
    N = n;
    if(mode=="SQ"){
        if (method=="ADM") generate_SQ_for_ADM();
    }
    generate_SQ_for_ADM();
}

void initialValueGen::generate_SQ_for_ADM(){
    rho = vector<double>(N);
    unsigned int n_left = (int)(.4*N), n_right = (int)(.6*N);
    for(size_t i=0;i<n_left;i++) rho[i] = 0;
    for(size_t i=n_left;i<n_right;i++) rho[i] = 1;
    for(size_t i=n_right;i<N;i++) rho[i] = 0;
}
