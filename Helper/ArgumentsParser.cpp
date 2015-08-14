#include "ArgumentsParser.h"

using namespace ME;

ArgumentsParser::ArgumentsParser(int &argc, char** argv) {

    for(int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            std::string tmpString(argv[i]);
            tmpString = tmpString.substr(1);
            mArguments[tmpString] = argv[i + 1];
            i++;
        }
    }
}

bool ArgumentsParser::hasArgument(const std::string &argumentName) {
    if (mArguments.find(argumentName) != mArguments.end()) {
        return true;
    } else {
        return false;
    }
}

std::string ArgumentsParser::getArgument(const std::string &argumentName) {
    return mArguments[argumentName];
}
