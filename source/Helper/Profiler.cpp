#include "Profiler.h"
#include "Engine/MedievalEngine.h"

using namespace ME;


std::map<std::string, MEUInt64> Profiler::Records;
Profiler::Type Profiler::mType = Profiler::Type::MICROSECONDS;

Profiler::Profiler(char* functionName, char* text) {
    std::string strFunctioName = std::string(functionName);
    std::string strText        = std::string(text);

    mFunctionName = strFunctioName;

    if (strText != "") {
        mFunctionName = mFunctionName + " " + strText;
    }

    mClock.restart();
}

Profiler::~Profiler() {
    Profiler::Records[mFunctionName] = mClock.getMicroSeconds();
}

void Profiler::setOutputType(const Profiler::Type& type) {
    Profiler::mType = type;
}

void Profiler::printRecords() {
    auto it  = Profiler::Records.begin();
    auto end = Profiler::Records.end();

    std::cout << "-------------------PROFILER-------------------" << std::endl;
    for(;it != end; it++) {
        std::cout << it->first << ": ";

        switch(Profiler::mType) {
        case Profiler::Type::SECONDS:
            std::cout << Clock::getSeconds(it->second) << "s";
            break;
        case Profiler::Type::MILLISECONDS:
            std::cout << Clock::getMilliSeconds(it->second) << "m";
            break;
        default:
            std::cout << it->second << "u"; // Default to microseconds
        }

        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------" << std::endl;
}

void Profiler::printRecords(MedievalEngine* engine) {
    auto it  = Profiler::Records.begin();
    auto end = Profiler::Records.end();

    // We dont load our debug text on the resource manager since we dont
    // want to create any overhead and put stuff on there
    sf::Text debugText;
    sf::Font* font = engine->getResourceManager()->getResource<Font>(Font::DEFAULT_FONT)->getResourcePointer();

    debugText.setFont(*font);
    debugText.setCharacterSize(14);

    std::string finalDebugText;

    finalDebugText = "PROFILER\n";

    for(;it != end; it++) {
        finalDebugText = finalDebugText + std::string(it->first) +  ": ";

        switch(Profiler::mType) {
        case Profiler::Type::SECONDS:
            finalDebugText = finalDebugText + std::to_string(Clock::getSeconds(it->second)) + "s";
            break;
        case Profiler::Type::MILLISECONDS:
            finalDebugText = finalDebugText + std::to_string(Clock::getMilliSeconds(it->second)) + "m";
            break;
        default:
            finalDebugText = finalDebugText + std::to_string(it->second) + "u"; // Default to microseconds
        }

        finalDebugText = finalDebugText + "\n";
    }
    debugText.setString(finalDebugText);

    engine->getWindow()->getWindowPtr()->draw(debugText);
}
