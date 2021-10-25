#include <iostream>

#include "editDistance.h"

#include "../../string.h"

using bud::string;

unsigned long getEdit(string f, string s){
    unsigned long a=f.size(), b=s.size();
    // std::cout << a << std::endl << b << std::endl;
    unsigned long d[b+1][a+1];
    // int** d = new int*[a+1];
    // for(unsigned long i=0;i<a+1;i++){
    //     d[i] = new int[b+1];
    // }


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
    // std::cout << "Test" << std::endl;
    // int fin = d[a][b];
    // for(unsigned long i=0;i<b+1;i++){
    //     for(unsigned long j=0;j<a+1;j++){
    //         std::cout << d[i][j] << ' ';
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << d[b][a] << std:: endl;
    return d[b][a];
}
