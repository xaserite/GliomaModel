#include <string>
#include <iostream>
#include <AdvectionDiffusionMethod.h>
#include <GliomaModel.h>
#include <initialValueGen.h>
#include <methodParams.h>
#include <velocitySpace.h>

using namespace std;

void ADM(string IN_PARAMETERS,string IN_VSPACE,string OUT_VALUES){
    methodParameters P(IN_PARAMETERS);
    initialValueGen iV(P.N_spatialPoints(),"SQ","ADM");
    AdvectionDiffusionMethod M(P,&iV);
    M.compute();
    M.write_toGnuplot(OUT_VALUES);
}

void GM(string IN_PARAMETERS,string IN_VSPACE,string OUT_VALUES){
    methodParameters P(IN_PARAMETERS);
    initialValueGen iV(P.N_spatialPoints(),"SQ","ADM");
    velocitySpace V(IN_VSPACE,true);
    //velocitySpace V("vSpace.data",false);
    //V.GM_fill_E(&P);
    GliomaModel M(P,&V,&iV);
    M.compute();
    M.write_toGnuplot(OUT_VALUES);
}

int main(int argc,const char *argv[]){
    string IN_PARAMETERS, IN_VALUES, IN_VSPACE, OUT_VALUES;
    IN_PARAMETERS = (argc>=2) ? argv[1] : "param.data";
    IN_VSPACE = (argc>=3) ? argv[2] : "vSpace.data";
    OUT_VALUES = (argc>=4) ? argv[3] : "rho.data";
    //ADM();
    GM(IN_PARAMETERS,IN_VSPACE,OUT_VALUES);
    return 0;
}
