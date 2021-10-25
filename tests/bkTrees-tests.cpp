#include "../lib/include/catch2/catch.hpp"

#include "../src/entry.h"
#include "../src/string.h"
#include "../src/bkTrees/bkTree.h"
#include <iostream>

using simple::string;
using simple::vector;

TEST_CASE("simple bk test", "[bk_tests1]")
{
    const vector<string*>* vec;




    // bkTree temp(string("hell"));

    // temp.add(string("help"));
    // temp.add(string("shell"));
    // temp.add(string("smell"));
    // temp.add(string("fell"));
    // temp.add(string("felt"));
    // temp.add(string("oops"));
    // temp.add(string("pop"));
    // temp.add(string("oouch"));
    // temp.add(string("halt"));
    // for(auto x: temp.getSimilars(string("ops"))){
    //     std::cout << x.m_text << std::endl;
    // }
    // REQUIRE(temp.getSimilars(string("ops")).size() == 2);

}

TEST_CASE("more bk test", "[bk_tests2]")
{
    // bkTree temp(string("hell"));

    // temp.add(string("help"));
    // temp.add(string("shell"));
    // temp.add(string("smell"));
    // temp.add(string("fell"));
    // temp.add(string("felt"));
    // temp.add(string("oops"));
    // temp.add(string("pop"));
    // temp.add(string("oouch"));
    // temp.add(string("halt"));
    // for(auto x: temp.getSimilars(string("helt"))){
    //     std::cout << x.m_text << std::endl;
    // }
    // REQUIRE(temp.getSimilars(string("helt")).size() == 6);

}