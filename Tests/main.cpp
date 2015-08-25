#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "Helper/Vect2.cpp"

TEST_CASE( "Vect2 tests", "[Vect2]" ) {

    ME::Vect2i v1;

    REQUIRE( v1.x == 0 );
    REQUIRE( v1.y == 0 );

    v1.x = 10;
    v1.y = 20;

    REQUIRE( v1.x == 10);
    REQUIRE( v1.y == 20);

    ME::Vect2i v2(5, 5);

    REQUIRE( v2.x == 5);
    REQUIRE( v2.y == 5);

    ME::Vect2i v3 = v2;

    REQUIRE( v2 == v3);
    REQUIRE( v1 != v3);
}
