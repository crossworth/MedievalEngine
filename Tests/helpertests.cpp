#include <Config.h>

#ifdef TEST
#include <ThirdParty/Catch.h>
#include <Helper/ArgumentsParser.h>
#include <Helper/CFGParser.h>


TEST_CASE( "Arguments are parsed", "[ArgumentsParser]" ) {
    int argc    = 3;
    char *argv[argc] = {
       "programName",
       "-config",
       "test.cfg"
    };

    ME::ArgumentsParser mTest(argc, argv);

    REQUIRE(mTest.hasArgument("config"));
    REQUIRE(mTest.getArgument("config") == "test.cfg");

}


#endif
