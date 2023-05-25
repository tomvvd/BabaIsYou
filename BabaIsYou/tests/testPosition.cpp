#include <catch2/catch_test_macros.hpp>
#include "../../BabaIsYou/src/game/Position.h"

TEST_CASE( "Test of Position") {
    Position pos{1,1};

    SECTION("Test Method next(...) : DOWN direction good"){
        bool res = pos.next(Direction::DOWN).getRow() == 2 && pos.next(Direction::DOWN).getColumn()==1;
        REQUIRE(res);
    }
    SECTION("Test Method next(...) : UP direction good"){
        bool res = pos.next(Direction::UP).getRow() == 0 && pos.next(Direction::UP).getColumn()==1;
        REQUIRE(res);
    }
    SECTION("Test Method next(...) : LEFT direction good"){
        bool res = pos.next(Direction::LEFT).getRow() == 1 && pos.next(Direction::LEFT).getColumn()==0;
        REQUIRE(res);
    }
    SECTION("Test Method next(...) : RIGHT direction good"){
        bool res = pos.next(Direction::RIGHT).getRow() == 1 && pos.next(Direction::RIGHT).getColumn()==2;
        REQUIRE(res);
    }
}
