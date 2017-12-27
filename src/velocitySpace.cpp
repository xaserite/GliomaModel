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

void velocitySpace::band_fill_E(methodParameters *P, unsigned int offset, double drift){
    if(_dim!=2 && _N!=4) return;
    unsigned _xN = P->N_xPoints(),
        _midN = _xN/2 + _xN%2,
        _LN = _midN - offset,
        _RN = _midN + offset + 1-_xN%2;
    double dominant_speed = 1+drift,
        inferior_speed = 1-drift;
    for(size_t i=0;i<_xN;i++){
        for(size_t j=0;j<_LN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
        for(size_t j=_LN;j<_RN;j++){
            _E[i*_Ny*_N + j*_N + 0] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 1] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 2] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 3] = inferior_speed;
        }
        for(size_t j=_RN;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
    }
}

void velocitySpace::cross_fill_E(methodParameters *P, unsigned int offset, double drift){
    if(_dim!=2 && _N!=4) return;
    unsigned _xN = P->N_xPoints(),
        _midN = _xN/2 + _xN%2,
        _LN = _midN - offset,
        _RN = _midN + offset + 1-_xN%2;
    double dominant_speed = 1+drift,
        inferior_speed = 1-drift;
    for(size_t i=0;i<_LN;i++){
        for(size_t j=0;j<_LN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
        for(size_t j=_LN;j<_RN;j++){
            _E[i*_Ny*_N + j*_N + 0] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 1] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 2] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 3] = inferior_speed;
        }
        for(size_t j=_RN;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
    }
    for(size_t i=_LN;i<_RN;i++){
        for(size_t j=0;j<_LN;j++){
            _E[i*_Ny*_N + j*_N + 0] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 1] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 2] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 3] = dominant_speed;
        }
        for(size_t j=_LN;j<_RN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
        for(size_t j=_RN;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 1] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 2] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 3] = dominant_speed;
        }
    }
    for(size_t i=_RN;i<_xN;i++){
        for(size_t j=0;j<_LN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
        for(size_t j=_LN;j<_RN;j++){
            _E[i*_Ny*_N + j*_N + 0] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 1] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 2] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 3] = inferior_speed;
        }
        for(size_t j=_RN;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
    }
}

void velocitySpace::T_fill_E(methodParameters *P, unsigned int offset, double drift){
    if(_dim!=2 && _N!=4) return;
    unsigned _xN = P->N_xPoints(),
        _midN = _xN/2 + _xN%2,
        _LN = _midN - offset,
        _RN = _midN + offset + 1-_xN%2;
    double dominant_speed = 1+drift,
        inferior_speed = 1-drift;
    for(size_t i=0;i<_LN-1;i++){
        for(size_t j=0;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
    }{unsigned int i = _LN-1;
        for(size_t j=0;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 2;
            _E[i*_Ny*_N + j*_N + 1] = 2;
            _E[i*_Ny*_N + j*_N + 2] = 0;
            _E[i*_Ny*_N + j*_N + 3] = 0;
        }
    }
    for(size_t i=_LN;i<_RN;i++){
        for(size_t j=0;j<_LN;j++){
            _E[i*_Ny*_N + j*_N + 0] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 1] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 2] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 3] = dominant_speed;
        }
        for(size_t j=_LN;j<_RN;j++){
            _E[i*_Ny*_N + j*_N + 0] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 1] = inferior_speed;
            _E[i*_Ny*_N + j*_N + 2] = dominant_speed;
            _E[i*_Ny*_N + j*_N + 3] = dominant_speed;
        }
        for(size_t j=_RN;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
    }
    for(size_t i=_RN;i<_xN;i++){
        for(size_t j=0;j<_xN;j++){
            _E[i*_Ny*_N + j*_N + 0] = 1;
            _E[i*_Ny*_N + j*_N + 1] = 1;
            _E[i*_Ny*_N + j*_N + 2] = 1;
            _E[i*_Ny*_N + j*_N + 3] = 1;
        }
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
