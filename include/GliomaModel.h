#ifndef GLIOMAMODEL_H
#define GLIOMAMODEL_H

#include <PDEmethod.h>
#include <vector>

struct velocitySpace{
    vector<double> E, w, v;
    unsigned int N;
};

using namespace std;

class GliomaModel : public PDEmethod
{
    public:
        GliomaModel(){}
        ~GliomaModel(){}

    protected:

    private:
        vector<double> g, rho;
        velocitySpace V;
};

#endif // GLIOMAMODEL_H
