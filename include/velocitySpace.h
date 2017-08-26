#ifndef VELOCITYSPACE_H_INCLUDED
#define VELOCITYSPACE_H_INCLUDED

#include <string>
#include <fstream>
#include <vector>
#include <methodParams.h>

using namespace std;

class velocitySpace{
    public:
        velocitySpace(){};
        velocitySpace(string filename,bool Do_read_E);
        ~velocitySpace();

        void GM_fill_E(methodParameters *P);
        double E(unsigned int j,unsigned int i);
        double w(unsigned int i);
        double v(unsigned int i);
        unsigned int N();

    private:
        ifstream FILESTREAM;
        vector<double> _w, _v, _E;
        unsigned int _N, _Nx;
        bool is_E_const, do_read_E;

        void read_E();
};

#endif // VELOCITYSPACE_H_INCLUDED
