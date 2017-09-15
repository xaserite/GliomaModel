#include <string>
#include <cstring>
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
    velocitySpace V(IN_VSPACE,true);
    AdvectionDiffusionMethod M(P,&V,&iV);
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
    if(argc<2){
        cout << "Too few arguments.\nSyntax: "
             << argv[0] << " -ADM/-GM [,in_param_path] [,in_vSpace_path] [,out_path]";
        return -1;
    }
    IN_PARAMETERS = (argc>=3) ? argv[2] : "param.data";
    IN_VSPACE = (argc>=4) ? argv[3] : "vSpace.data";
    OUT_VALUES = (argc>=5) ? argv[4] : "rho_correct.data";
    if( strcmp(argv[1],"-ADM") == 0){
        cout << "Running Advection-Diffusion-Model.\nOutput in "
             << OUT_VALUES << endl;
        ADM(IN_PARAMETERS,IN_VSPACE,OUT_VALUES);
    }else if( strcmp(argv[1],"-GM") == 0){
        cout << "Running GlioMath-Model.\nOutput in "
             << OUT_VALUES << endl;
        GM(IN_PARAMETERS,IN_VSPACE,OUT_VALUES);
    }else{
        cout << "Invalid argument.\nSyntax: "
             << argv[0] << " -ADM/-GM [,in_param_path] [,in_vSpace_path] [,out_path]";
        return -2;
    }
    return 0;
}
