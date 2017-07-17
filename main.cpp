#include <string>
#include <iostream>
#include <AdvectionDiffusionMethod.h>
#include <initialValueGen.h>
#include <methodParams.h>

using namespace std;

int main(){
    methodParameters P("param.data");
    initialValueGen iV(P.N_spatialPoints(),"SQ","ADM");
    AdvectionDiffusionMethod M(P,&iV);
    M.compute();
    M.write_toGnuplot("rho.data");
    return 0;
}
