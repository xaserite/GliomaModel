#include <velocitySpace.h>

velocitySpace::velocitySpace(string filename,bool Do_read_E){
    do_read_E = Do_read_E;
    FILESTREAM.open(filename,ios::in);
    FILESTREAM >> _dim >>_N;
    if(_dim == 1)
        FILESTREAM >> _Nx;
    else if(_dim == 2)
        FILESTREAM >> _Nx >> _Ny;
    else
        throw "exception: velocity space dim must be 0,1 or 2";
    read_w();
    read_v();
    read_E();
    FILESTREAM.close();
}

velocitySpace::~velocitySpace(){
    _v.clear();
    _w.clear();
    _E.clear();
}

void velocitySpace::GM_fill_E(methodParameters *P){
    unsigned int _xN = P->N_xPoints();
    if(_N!=2) return;
    _E = vector<double>(_xN * 2);
    for(size_t i=0;i<_xN;i++){
        _E[i] = (double)i/_xN;
        _E[_xN+i] = 1-_E[i];
    }
}

double velocitySpace::E(unsigned int k, unsigned int i, unsigned int j){
    if(_Nx==1) return _E[k];
    else if(_Ny==1) return _E[i*_N + k];
    else return _E[i*_Ny*_N + j*_N + k];
}

double velocitySpace::w(unsigned int i){
    return _w[i];
}

double velocitySpace::v(unsigned int j,unsigned int d){
    if(_dim==0||_dim==1) return _v[j];
    else return _v[j*_dim + d];
}

unsigned int velocitySpace::N(){
    return _N;
}

unsigned int velocitySpace::dim(){
    return _dim;
}

void velocitySpace::read_E(){
    _E = vector<double>(_N*_Nx*_Ny);
    for(size_t i=0;i<_Nx;i++)
        for(size_t j=0;j<_Ny;j++)
            for(size_t k=0;k<_N;k++)
                FILESTREAM >> _E[i*_Ny*_N + j*_N + k];
}

void velocitySpace::read_v(){
    unsigned int D = (_dim==0) ? 1 : _dim;
    _v= vector<double>(_N*D);
    for(size_t j=0;j<_N;j++)
        for(size_t i=0;i<D;i++)
            FILESTREAM >> _v[j*D+i];
}

void velocitySpace::read_w(){
    _w = vector<double>(_N);
    for(size_t j=0;j<_N;j++)
        FILESTREAM >> _w[j];
}
