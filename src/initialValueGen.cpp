#include "initialValueGen.h"

initialValueGen::initialValueGen(unsigned nx,unsigned int ny, string mode,string method){
    Nx = nx; Ny = ny;
    if(mode=="SQ"){
        if (method=="ADM") generate_SQ_for_ADM();
    }
    generate_SQ_for_ADM();
}

void initialValueGen::generate_SQ_for_ADM(){
    rho = vector<double>(Nx*Ny);
    unsigned int nx_left = (int)(.4*Nx), nx_right = (int)(.6*Nx);
    unsigned int ny_left = (int)(.4*Ny), ny_right = (int)(.6*Ny);
    for(size_t j=0;j<nx_left;j++)
        for(size_t i=0;i<Ny;i++) rho[i] = 0;
    for(size_t j=nx_left;j<nx_right;j++){
        for(size_t i=0;i<ny_left;i++) rho[i] = 0;
        for(size_t i=ny_left;i<ny_right;i++) rho[i] = 1;
        for(size_t i=ny_right;i<Ny;i++) rho[i] = 0;
    }
    for(size_t j=nx_right;j<Nx;j++)
        for(size_t i=0;i<Ny;i++) rho[i] = 0;
}
