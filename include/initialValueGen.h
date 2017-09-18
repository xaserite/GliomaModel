#ifndef INITIALVALUEGEN_H
#define INITIALVALUEGEN_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class initialValueGen
{
    public:
        initialValueGen(unsigned int Nx, unsigned int Ny, string mode,string method);
        ~initialValueGen(){
            rho.clear();
        }
        vector<double>* get_rho() { return &rho; }

    protected:

    private:
        unsigned int Nx, Ny;
        vector<double> rho;

        void generate_SQ_for_ADM();
};

#endif // INITIALVALUEGEN_H
