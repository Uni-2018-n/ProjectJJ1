#include "../lib/include/catch2/catch.hpp"

#include "../src/string.h"
#include "../src/bkTrees/bkTree.h"
#include <iostream>
#include <stdexcept>

using bud::string;
using bud::vector;

TEST_CASE("simple bk test", "[bk_tests1]")
{
	vector<string*> vec;
	vec.emplace_back(new string("hell"));
	vec.emplace_back(new string("help"));
	vec.emplace_back(new string("shell"));
	vec.emplace_back(new string("smell"));
	vec.emplace_back(new string("fell"));
	vec.emplace_back(new string("felt"));
	vec.emplace_back(new string("oops"));
	vec.emplace_back(new string("pop"));
	vec.emplace_back(new string("oouch"));
	vec.emplace_back(new string("halt"));

	try
	{
		bkTree temp(vec);
		vector<string*> p = temp.find(string("ops"), 2);
		for (auto x : p)
		// {
		// 	std::cout << x->m_text << std::endl;
		// }
		REQUIRE(p.size() == 2);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
	for(auto* x: vec){
		delete x;
	}
}

TEST_CASE("more bk test", "[bk_tests2]")
{
	vector<string*> vec;
	vec.emplace_back(new string("hell"));
	vec.emplace_back(new string("help"));
	vec.emplace_back(new string("shell"));
	vec.emplace_back(new string("smell"));
	vec.emplace_back(new string("fell"));
	vec.emplace_back(new string("felt"));
	vec.emplace_back(new string("oops"));
	vec.emplace_back(new string("pop"));
	vec.emplace_back(new string("oouch"));
	vec.emplace_back(new string("halt"));

	try
	{
		bkTree temp(vec);
		vector<string*> p = temp.find(string("helt"), 2);
		// for (auto x : p)
		// {
		// 	std::cout << x->m_text << std::endl;
		// }
		REQUIRE(p.size() == 6);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
	for(auto* x: vec){
		delete x;
	}
}

TEST_CASE("empty vec bk test", "[bk_tests3]")
{
	vector<string*> vec;

	try
	{
		bkTree temp(vec);
		vector<string*> p = temp.find(string("helt"), 2);
		// for (auto x : p)
		// {
		// 	std::cout << x->m_text << std::endl;
		// }
		REQUIRE(p.size() == 6);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
	for(auto* x: vec){
		delete x;
	}
}
