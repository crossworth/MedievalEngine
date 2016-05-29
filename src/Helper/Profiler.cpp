#include "Profiler.h"
#include "Engine/MedievalEngine.h"

using namespace ME;


std::map<std::string, MEUInt64> Profiler::Records;
std::map<MEUInt64, std::string> Profiler::recordsSorted;

Profiler::Type Profiler::mType = Profiler::Type::MICROSECONDS;

bool Profiler::mIsVisible    = false;
bool Profiler::mIsLuaExposed = false;
Clock Profiler::mClockSort;
sf::Text Profiler::mDebugText;

unsigned int Profiler::mUpdateTime = 1000;


void Profiler::setUpdateTime(unsigned int time) {
    Profiler::mUpdateTime = time;
}

void Profiler::exposeLuaAPI() {
    Profiler::mIsLuaExposed = true;

    LuaAPI::state.set_function("profiler_toggle", [](void){
        if (Profiler::isVisible()) {
            Profiler::setVisible(false);
        } else {
            Profiler::setVisible(true);
        }
    });

    LuaFunctions::store("profiler_toggle");

    LuaAPI::state.set_function("profiler_set_update_time", &Profiler::setUpdateTime);
    LuaFunctions::store("profiler_set_update_time");

    LuaAPI::state.set_function("profiler_set_output_type", [](int type){
        Profiler::Type tmpType;

        switch(type) {
            case 1:
                tmpType = Profiler::Type::SECONDS;
                break;
            case 2:
                tmpType = Profiler::Type::MILLISECONDS;
                break;
            default:
                tmpType = Profiler::Type::MICROSECONDS;
        }

        Profiler::setOutputType(tmpType);
    });
    LuaFunctions::store("profiler_set_output_type");

}

Profiler::Profiler(const char* functionName, const char* text) {
    std::string strFunctioName = std::string(functionName);
    std::string strText        = std::string(text);

    mFunctionName = strFunctioName;

    if (strText != "") {
        mFunctionName = mFunctionName + " " + strText;
    }

    if (Profiler::mIsLuaExposed == false) {
        Profiler::exposeLuaAPI(); // expose all Lua functions
    }

    mClock.restart();
}

Profiler::~Profiler() {
    Profiler::Records[mFunctionName] = mClock.getMicroSeconds();
}

void Profiler::setOutputType(const Profiler::Type& type) {
    Profiler::mType = type;
}

bool Profiler::isVisible() {
    return Profiler::mIsVisible;
}

void Profiler::setVisible(bool visible) {

    Profiler::mIsVisible = visible;

    if (Profiler::isVisible()) {
        mClockSort.restart();
    }
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
    static bool textInitialzied = false;

    if (textInitialzied == false) {
        textInitialzied = true;
        // We dont load our debug text on the resource manager since we dont
        // want to create any overhead and put stuff on there
        static sf::Font* font;
        font = engine->getResourceManager()->getResource<Font>(Font::DEFAULT_FONT)->getResourcePointer();
        
        Profiler::mDebugText.setFont(*font);
        Profiler::mDebugText.setCharacterSize(14);
    }


    // we have a sorted by value map by swaping the key/value

    // resort the records every UPDATE TIME seconds or if it's size dont math the other map
    if ((Profiler::recordsSorted.size() != Profiler::Records.size()) || mClockSort.getMilliSeconds() > Profiler::mUpdateTime) {
        Profiler::recordsSorted.clear();

        // our iterator for the sorted by key map
        auto    itUnsorted  = Profiler::Records.begin();
        auto endUnsorted = Profiler::Records.end();

        // simple swap
        for(;itUnsorted != endUnsorted; itUnsorted++) {
            Profiler::recordsSorted[itUnsorted->second] = itUnsorted->first;
        }
        
        mClockSort.restart();
    }

    // our iterator's, 
    // since we want to get the higher values first
    // we get the rbegin and rend
    auto it  = Profiler::recordsSorted.rbegin();
    auto end = Profiler::recordsSorted.rend();

    std::string finalDebugText;
    finalDebugText = "PROFILER - update every " + Kit::int_str(Profiler::mUpdateTime) + "u\n";

    // it it's at the end so we decrease the iterator
    for(;it != end; it++) {
        // separate by colon
        finalDebugText = finalDebugText + std::string(it->second) +  ": ";

        switch(Profiler::mType) {
        case Profiler::Type::SECONDS:
            finalDebugText = finalDebugText + std::to_string(Clock::getSeconds(it->first)) + "s";
            break;
        case Profiler::Type::MILLISECONDS:
            finalDebugText = finalDebugText + std::to_string(Clock::getMilliSeconds(it->first)) + "m";
            break;
        default:
            finalDebugText = finalDebugText + std::to_string(it->first) + "u"; // Default to microseconds
        }

        finalDebugText = finalDebugText + "\n";

    }

    Profiler::mDebugText.setString(finalDebugText);

    engine->getWindow()->getWindowPtr()->draw(Profiler::mDebugText);
}
