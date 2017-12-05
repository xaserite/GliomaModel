#include "CFL_finder.h"

CFL_finder::CFL_finder(GliomaModel *g){
    G = g;
    tN_lower = 4;
    _xN = G->get_N_x();
    tN_upper = 1; // treated as infinity
}

unsigned int CFL_finder::tN(){
    return _tN;
}

unsigned int CFL_finder::xN(){
    return _xN;
}

double CFL_finder::CFL_number(){
    return _CFL_number;
}

void CFL_finder::analyse(){
    bisection(tN_lower);
}

void CFL_finder::bisection(unsigned int tN_proposed){
    if(std::abs( (int)(tN_lower-tN_upper) ) <3){
        _tN = tN_proposed;
        _CFL_number = (double)_tN/_xN;
        return;
    }
    G->set_N_timeSteps(tN_proposed);
    G->compute_incomplete();
    if(G->was_monotonicity_preserved()){
        tN_upper = tN_proposed;
        bisection( (int)(0.5*(tN_lower+tN_upper)) );
    }else{
        tN_lower = tN_proposed +1;
        if(tN_upper==1) bisection(2*tN_proposed);
        else bisection( (int)(0.5*(tN_lower+tN_upper)) );
    }
}

void CFL_finder::append_toFile(std::string filename){
    std::ofstream FILESTREAM(filename,std::fstream::out|std::fstream::app);
    FILESTREAM << _xN << "\t" << _tN << "\t" << _CFL_number << endl;
    FILESTREAM.close();
}
