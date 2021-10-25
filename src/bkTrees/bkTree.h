#ifndef BKTREE_HPP
#define BKTREE_HPP

#include "../string.h"
#include "../core.h"
#include "../vector.h"

class bkNode {
    bud::string* str;

    bud::vector<bkNode*> childs = bud::vector<bkNode*>(2*MAX_WORD_LENGTH, nullptr);
public:
    bkNode(bud::string* s);
    void add(bud::string* s);
    bud::vector<bud::string*> find(const bud::string& s, int tol);
};

class bkTree {
    bkNode* root;
    void add(bud::string* s);
public:
    bkTree(const bud::vector<bud::string*>& vec);
    bud::vector<bud::string*> find(const bud::string& s, int tol);
};

#endif // !BKTREE_HPP
