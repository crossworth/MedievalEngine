#include "ArgumentsParser.h"

using namespace ME;

ArgumentsParser::ArgumentsParser(int& argc, char** argv) {
    // We initialize the i to one since the first argument is always
    // the program name
    for(int i = 1; i < argc; i++) {
        // if the current argument start with -
        // we are reading a option
        if (argv[i][0] == '-') {
            // better work with std::string's
            std::string tmpString(argv[i]);
            // so we read the option name
            tmpString = tmpString.substr(1);
            // then we store the next value after the option

            // TODO(Pedro): We could implement a check here to verify if the
            // next argument start with - if so we could log a error message
            mArguments[tmpString] = argv[i + 1];
            i++;
        }
    }
}

bool ArgumentsParser::hasArgument(const std::string& argumentName) {
    if (mArguments.find(argumentName) != mArguments.end()) {
        return true;
    } else {
        return false;
    }
}

std::string ArgumentsParser::getArgument(const std::string& argumentName) {
    // TODO(Pedro): type check if we have the variable first?
    return mArguments[argumentName];
}
