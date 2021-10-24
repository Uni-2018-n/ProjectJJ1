#ifndef BKTREE_HPP
#define BKTREE_HPP

#include "../string.h"
#include "../core.h"
#include "../vector.h"

class bkNode {
    simple::string str = simple::string("");

    simple::vector<bkNode*> childs = simple::vector<bkNode*>(2*MAX_WORD_LENGTH, nullptr);
public:
    bkNode(simple::string s);
    void add(simple::string s);
    simple::vector<simple::string> getSimilars(simple::string s);
};

class bkTree {
    bkNode* root;
public:
    bkTree(simple::string s);
    void add(simple::string s);
    simple::vector<simple::string> getSimilars(simple::string s);
};

#endif // !BKTREE_HPP

