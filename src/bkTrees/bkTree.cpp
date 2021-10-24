#include "bkTree.h"
#include "../string.h"
#include "../vector.h"

#include "appMatching/editDistance.h"

using simple::string;
using simple::vector;

bkNode::bkNode(string s){
    str = s;
}

void bkNode::add(string s){
    unsigned long curr = getEdit(str, s);
    if(childs[curr] == nullptr){
        childs[curr] = new bkNode(s);
    }else{
        childs[curr]->add(s);
    }
}

simple::vector<string> bkNode::getSimilars(string s){
    vector<string> fin;
    if(str != string("")){
        int temp = getEdit(str, s);
        if(temp < EDIT_TOL){
            fin.emplace_back(str);
        }

        for(int i = temp - EDIT_TOL < 0 ? 1 : temp - EDIT_TOL; i < temp+EDIT_TOL;i++){
            // fin.append(childs[i]->getSimilars(s));
        }
    }
    return fin;
}

bkTree::bkTree(string s){
    root = new bkNode(s);
}

void bkTree::add(string s){
    root->add(s);
}

vector<string> bkTree::getSimilars(string s){
    return root->getSimilars(s);
}
