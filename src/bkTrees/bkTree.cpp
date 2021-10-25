#include "bkTree.h"
#include "../string.h"
#include "../vector.h"

#include "appMatching/editDistance.h"
#include <iostream>

using bud::string;
using bud::vector;

bkNode::bkNode(string* s) { str = s; }

void bkNode::add(string* s)
{
	unsigned long curr = getEdit(*str, *s);
	if (childs[curr] == nullptr)
	{
		childs[curr] = new bkNode(s);
	}
	else
	{
		childs[curr]->add(s);
	}
}

bud::vector<bud::string*> bkNode::find(const bud::string& s, int tol)
{
	vector<string*> fin;
	if (*str != string(""))
	{
		int temp = getEdit(*str, s);
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
bkTree::bkTree(const bud::vector<bud::string*>& vec)
{
	if (vec.size() == 0)
	{
		throw "Vector is empty!";
		return;
	}
	root = new bkNode(vec[0]);
	for (unsigned i = 1; i < vec.size(); i++)
	{
		this->add(vec[i]);
	}
}

void bkTree::add(string* s) { root->add(s); }

bud::vector<bud::string*> bkTree::find(const bud::string& s, int tol) { return root->find(s, tol); }
