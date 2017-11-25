#ifndef CFL_FINDER_H
#define CFL_FINDER_H

#include <GliomaModel.h>

class CFL_finder
{
    public:
        CFL_finder(){}
        ~CFL_finder(){}

    private:
        double _CFL_number;
        unsigned int _xN, _tN;
        GliomaModel *G;
};

#endif // CFL_FINDER_H
