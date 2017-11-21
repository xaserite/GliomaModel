#include "initialValueGen.h"
#include <iostream>

initialValueGen::initialValueGen(unsigned nx,unsigned int ny, string mode,string method){
    Nx = nx; Ny = ny;
    if(mode=="SQ"){
        if (method=="ADM") generate_SQ_for_ADM();
    }
}

void initialValueGen::generate_SQ_for_ADM(){
    rho = vector<double>(Nx*Ny);
    unsigned int nx_left = (int)(.45*Nx), nx_right = (int)(.55*Nx);
    unsigned int ny_left = (int)(.45*Ny), ny_right = (int)(.55*Ny);
    for(size_t j=0;j<nx_left;j++)
        for(size_t i=0;i<Ny;i++) rho[j+i*Nx] = 0;
    for(size_t j=nx_left;j<nx_right;j++){
        for(size_t i=0;i<ny_left;i++) rho[j+i*Nx] = 0;
        for(size_t i=ny_left;i<=ny_right;i++) rho[j+i*Nx] = 1;
        for(size_t i=ny_right+1;i<Ny;i++) rho[j+i*Nx] = 0;
    }
    for(size_t j=nx_right;j<Nx;j++)
        for(size_t i=0;i<Ny;i++) rho[j+i*Nx] = 0;
}
