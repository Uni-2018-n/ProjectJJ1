#ifndef BKTREE_HPP
#define BKTREE_HPP

#include "../string.h"
#include "../core.h"
#include "../vector.h"
#include "../inverted_search_engine.h"

class bkNode
{
	bud::string* str;
	match_type type;
	bud::vector<bkNode*> childs = bud::vector<bkNode*>(2 * MAX_WORD_LENGTH, nullptr);

public:
	bkNode(bud::string* s, match_type m);
	~bkNode();
	void add(bud::string* s);
	bud::vector<bud::string*> find(const bud::string& s, int tol);
};

class bkTree : public inverted_search_engine
{
	bkNode* root;
	match_type type;
	void add(bud::string* s);
	bud::vector<bud::string*> findd(const bud::string& s, int tol) const;

public:
	bkTree(bud::vector<bud::vector<bud::string*>*>* queries, match_type m);
	~bkTree() override;

	bud::vector<bud::vector<bud::string>> find(bud::string& word) const override
	{
		return find(word, 0);
	}

	bud::vector<bud::vector<bud::string>> find(bud::string& word, int tol) const override;
};

#endif // !BKTREE_HPP
