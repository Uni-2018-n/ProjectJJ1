#include "../lib/include/catch2/catch.hpp"

#include "../src/entry.h"
#include "../src/string.h"
#include "../src/bkTrees/appMatching/editDistance.h"

using simple::string;

TEST_CASE("edit tests", "[edit_tests]")
{
	REQUIRE(eDistance() ==15);
}