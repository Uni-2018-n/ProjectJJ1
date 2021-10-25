#include "bkTree.h"
#include "../string.h"
#include "../vector.h"
#include "../inverted_search_engine.h"

#include "appMatching/editDistance.h"
#include <iostream>
#include <stdexcept>

using bud::string;
using bud::vector;

bkNode::bkNode(string* s, match_type m) { str = s; type = m; }

void bkNode::add(string* s)
{
	unsigned long curr;
	if(type == EDIT_DISTANCE){
		curr = getEdit(*str, *s);
	}else{
		curr = 0;
	}
	if (childs[curr] == nullptr)
	{
		childs[curr] = new bkNode(s, type);
	}
	else
	{
		childs[curr]->add(s);
	}
}
bkNode::~bkNode(){
	for(auto* x:childs){
		delete x;
	}
}

bud::vector<bud::string*> bkNode::find(const bud::string& s, int tol)
{
	vector<string*> fin;
	if (*str != string(""))
	{
		int temp;
		if(type == EDIT_DISTANCE){
			temp = getEdit(*str, s);
		}else{ 
			temp = -1;
		}

		if (temp <= tol)
		{
			fin.emplace_back(str);
		}
		for (unsigned long i = temp - tol < 0 ? 1 : unsigned(temp - tol); i <= unsigned(temp + tol);
			 i++)
		{
			if (childs[i] != nullptr)
			{
				vector<string*> t = childs[i]->find(s, tol);
				fin.insert(t.begin(), t.end());
			}
		}
	}
	return fin;
}

bkTree::bkTree(bud::vector<bud::vector<bud::string*>*>* queries, match_type m)//TODO
:inverted_search_engine(queries){
	type = m;
	if (m_words_from_all_queries.size() == 0)
	{
		throw std::invalid_argument("Vector is empty!");
		return;
	}
	root = new bkNode(m_words_from_all_queries[0], type);
	for (unsigned i = 1; i < m_words_from_all_queries.size(); i++)
	{
		this->add(m_words_from_all_queries[i]);
	}
}

bkTree::~bkTree(){
	delete root;
}

void bkTree::add(string* s) { root->add(s); }

bud::vector<bud::string*> bkTree::findd(const bud::string& s, int tol) { return root->find(s, tol); }
