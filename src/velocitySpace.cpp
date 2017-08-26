#include <velocitySpace.h>

velocitySpace::velocitySpace(string filename,bool Do_read_E){
    do_read_E = Do_read_E;
    FILESTREAM.open(filename,ios::in);
    FILESTREAM >> _N >> _Nx;
    is_E_const = (_Nx==1);
    _v = vector<double>(_N);
    _w = vector<double>(_N);
    _E = vector<double>(_N*_Nx);
    for(size_t j=0;j<_N;j++)
        FILESTREAM >> _v[j];
    for(size_t j=0;j<_N;j++)
        FILESTREAM >> _w[j];
    if (Do_read_E) read_E();
    FILESTREAM.close();
}

velocitySpace::~velocitySpace(){
    _v.clear();
    _w.clear();
    _E.clear();
}

void velocitySpace::GM_fill_E(methodParameters *P){
    unsigned int _xN = P->N_spatialPoints();
    if(_N!=2) return;
    for(size_t i=0;i<_xN;i++){
        _E[i] = (double)i/_xN;
        _E[_xN+i] = 1-_E[i];
    }
}

double velocitySpace::E(unsigned int j, unsigned int i){
    if(is_E_const) return _E[j];
    else return _E[j*_Nx+i];
}

double velocitySpace::w(unsigned int i){
    return _w[i];
}

double velocitySpace::v(unsigned int i){
    return _v[i];
}

unsigned int velocitySpace::N(){
    return _N;
}

void velocitySpace::read_E(){
    for(size_t j=0;j<_N;j++){
        for(size_t i=0;i<_Nx;i++)
            FILESTREAM >> _E[j*_Nx+i];
    }
}
