#include <string>
#include <iostream>
#include <AdvectionDiffusionMethod.h>
#include <GliomaModel.h>
#include <initialValueGen.h>
#include <methodParams.h>
#include <velocitySpace.h>

using namespace std;



void ADM(){
    methodParameters P("param.data");
    initialValueGen iV(P.N_xPoints(),"SQ","ADM");
    AdvectionDiffusionMethod M(P,&iV);
    M.compute();
    M.write_toGnuplot("rho.data");
}

void GM(){
    methodParameters P("param.data");
    initialValueGen iV(P.N_xPoints(),"SQ","ADM");
    //velocitySpace V("vSpace.data",true);
    velocitySpace V("vSpace.data",true);
    /*V.GM_fill_E(&P);
    GliomaModel M(P,&V,&iV);
    M.compute();
    M.write_toGnuplot("rho.data");*/
}

int main(){
    //ADM();
    GM();
    return 0;
}
