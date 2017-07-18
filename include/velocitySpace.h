#ifndef VELOCITYSPACE_H_INCLUDED
#define VELOCITYSPACE_H_INCLUDED

#include <string>
#include <fstream>

using namespace std;

class velocitySpace{
    public:
        velocitySpace(){};
        velocitySpace(string filename){
            ifstream FILESTREAM;
            FILESTREAM.open(filename,ios::in);
            FILESTREAM >> N;
            v = vector<double>(N);
            w = vector<double>(N);
            E = vector<double>(N);
            for(size_t j=0;j<N;j++)
                FILESTREAM >> v[j];
            for(size_t j=0;j<N;j++)
                FILESTREAM >> w[j];
            for(size_t j=0;j<N;j++)
                FILESTREAM >> E[j];
            FILESTREAM.close();
        }
        ~velocitySpace(){
            v.clear();
            w.clear();
            E.clear();
        }

        vector<double> E, w, v;
        unsigned int N;
};

#endif // VELOCITYSPACE_H_INCLUDED
