#ifndef BKTREE_HPP
#define BKTREE_HPP

#include "../string.h"
#include "../core.h"
#include "../vector.h"

class bkNode {
    simple::string* str;

    simple::vector<bkNode*> childs = simple::vector<bkNode*>(2*MAX_WORD_LENGTH, nullptr);
public:
    bkNode(simple::string* s);
    void add(simple::string* s);
    simple::vector<simple::string*> find(const simple::string& s);
};

class bkTree {
    bkNode* root;
public:
    bkTree(simple::vector<simple::string*>& vec);
    void add(simple::string* s);
    simple::vector<simple::string*> find(const simple::string& s);
};

#endif // !BKTREE_HPP

