#ifndef VELOCITYSPACE_H_INCLUDED
#define VELOCITYSPACE_H_INCLUDED

#include <string>
#include <fstream>

using namespace std;

class velocitySpace{
    public:
        velocitySpace(){};
        velocitySpace(string filename,bool Do_read_E){
            do_read_E = Do_read_E;
            FILESTREAM.open(filename,ios::in);
            FILESTREAM >> N >> Nx;
            is_E_const = (Nx==1);
            v = vector<double>(N);
            w = vector<double>(N);
            for(size_t j=0;j<N;j++)
                FILESTREAM >> v[j];
            for(size_t j=0;j<N;j++)
                FILESTREAM >> w[j];
            if (Do_read_E) read_E();
            FILESTREAM.close();
        }
        ~velocitySpace(){
            v.clear();
            w.clear();
            //free(_E);
        }
        void read_E(){
            _E = (double*) malloc(N*Nx);
            for(size_t j=0;j<N;j++){
                for(size_t i=0;i<Nx;i++)
                    FILESTREAM >> _E[j*Nx+i];
            }
        }
        void GM_fill_E(methodParameters *P){
            unsigned xN = P->N_spatialPoints();
            if(N!=2) return;
            _E = (double*)malloc(xN * 2 * sizeof(double));
            for(size_t i=0;i<xN;i++){
                _E[i] = (double)i/xN;
                _E[xN+i] = 1-_E[i];
            }
        }

        double E(unsigned j,unsigned i){
            if(is_E_const) return _E[j];
            else return _E[j*Nx+i];
        }

        ifstream FILESTREAM;
        vector<double> w, v;
        double* _E;
        unsigned int N, Nx;
        bool is_E_const, do_read_E;
};

#endif // VELOCITYSPACE_H_INCLUDED
