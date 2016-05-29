#ifndef ARGUMENTSPARSER_H
#define ARGUMENTSPARSER_H
#include <map>
#include <iostream>

namespace ME {

class ArgumentsParser {
public:
    ArgumentsParser(int& argc, char** argv);

    bool hasArgument(const std::string& argumentName);
    std::string getArgument(const std::string& argumentName);

private:
    std::map<std::string, std::string> mArguments;
};

}

#endif // ARGUMENTSPARSER_H
