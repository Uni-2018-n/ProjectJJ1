#include <iostream>

#include "editDistance.h"

#include "../../string.h"

using bud::string;

unsigned long getEdit(string f, string s){
    unsigned long a=f.size(), b=s.size();
    // std::cout << a << std::endl << b << std::endl;
    // unsigned long d[b+1][a+1];
    unsigned long** d = new unsigned long*[b+1];
    for(unsigned long i=0;i<b+1;i++){
        d[i] = new unsigned long[a+1];
    }


    for(unsigned long i=0;i<a+1;i++){
        d[0][i] = i;
    }
    for(unsigned long i=0;i<b+1;i++){
        d[i][0] = i;
    }


    for(unsigned long i=1;i<b+1;i++){
        for(unsigned long j=1;j<a+1;j++){
            if(f[j-1] == s[i-1]){
                d[i][j] = d[i-1][j-1];
            }else{
                if(d[i-1][j-1] <= d[i-1][j]){
                    if(d[i-1][j-1] <= d[i][j-1]){
                        d[i][j] = d[i-1][j-1]+1;
                    }else{
                        d[i][j] = d[i][j-1]+1;
                    }
                }else{
                    if(d[i-1][j] <= d[i][j-1]){
                        d[i][j] = d[i-1][j]+1;
                    }else{
                        d[i][j] = d[i][j-1]+1;
                    }
                }
            }
        }
    }
    unsigned long fin = d[b][a];
    for(unsigned long i=0;i<b+1;i++){
        delete[] d[i];
    }
    delete[] d;
    return fin;
}
