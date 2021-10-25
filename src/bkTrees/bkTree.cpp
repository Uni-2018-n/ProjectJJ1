#include "bkTree.h"
#include "../string.h"
#include "../vector.h"

#include "appMatching/editDistance.h"
#include <iostream>

using simple::string;
using simple::vector;

bkNode::bkNode(string* s){
    str = s;
}

void bkNode::add(string* s){
    unsigned long curr = getEdit(*str, *s);
    if(childs[curr] == nullptr){
        childs[curr] = new bkNode(s);
    }else{
        childs[curr]->add(s);
    }
}

simple::vector<simple::string*> bkNode::find(const simple::string& s){
    vector<string*> fin;
    if(*str != string("")){
        int temp = getEdit(*str, s);
        if(temp <= EDIT_TOL){
            fin.emplace_back(str);
        }
        for(unsigned long i = temp - EDIT_TOL < 0 ? 1 : unsigned(temp - EDIT_TOL); i <= unsigned(temp+EDIT_TOL);i++){
            if(childs[i] != nullptr){
                vector<string*> t = childs[i]->find(s);
                fin.insert(t.begin(), t.end());
            }
        }
    }
    return fin;
}
bkTree::bkTree(simple::vector<simple::string*>& vec){
    root = new bkNode(vec[0]);
    for(unsigned i=1;i<vec.size();i++){
        this->add(vec[i]);
    }
}

void bkTree::add(string* s){
    root->add(s);
}

simple::vector<simple::string*> bkTree::find(const simple::string& s){
    return root->find(s);
}
