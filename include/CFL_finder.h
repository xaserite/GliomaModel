#ifndef CFL_FINDER_H
#define CFL_FINDER_H

#include <GliomaModel.h>
#include <fstream>
#include <string>
#include <fstream>
class CFL_finder
{
    public:
        CFL_finder(GliomaModel *g);
        ~CFL_finder(){}

        unsigned int tN();
        unsigned int xN();
        double CFL_number();
        void analyse();
        void append_toFile(std::string filename);

    private:
        double _CFL_number;
        unsigned int _xN, _tN, tN_lower, tN_upper;
        GliomaModel *G;

        void bisection(unsigned int tN_proposed);
};

#endif // CFL_FINDER_H
