#include <iostream>

#include "hammingDistance.h"

#include "../../string.h"

using bud::string;

unsigned long getHamming(string f, string s){
    unsigned fin =0;
    for(unsigned i=0;i<f.size();i++){
        if(f[i] != s[i]){
            fin++;
        }
    }
    return fin;
}
