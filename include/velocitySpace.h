#ifndef VELOCITYSPACE_H_INCLUDED
#define VELOCITYSPACE_H_INCLUDED

#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <methodParams.h>

using namespace std;

class velocitySpace{
    public:
        velocitySpace(){};
        velocitySpace(string filename,bool Do_read_E);
        ~velocitySpace();

        void GM_fill_E(methodParameters *P);
        double E(unsigned int j,unsigned int i);
        double E(unsigned int k,unsigned int i,unsigned int j);
        double w(unsigned int j);
        double v(unsigned int j,unsigned d);
        unsigned int N();

        bool is_constant(){return is_E_const;}
        unsigned int dim();

    private:
        ifstream FILESTREAM;
        vector<double> _w, _v, _E;
        unsigned int _dim, _N, _Nx=1, _Ny=1;
        bool is_E_const, do_read_E;

        void read_v();
        void read_w();
        void read_E();
};

#endif // VELOCITYSPACE_H_INCLUDED
