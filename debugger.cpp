#include "debugger.h"

using namespace ME;

Debugger::Debugger() : debugToFile(false) , enableDebug(false) {
    enableDebug = DEBUG;


    if(DEBUG_FILE != "") {
        this->fileName = DEBUG_FILE;
        debugToFile    = true;
    }

    if (enableDebug) {
        std::cout << "DEBUGGER STARTED" << std::endl;

        if (debugToFile) {
            std::cout << "[FILE]: " << fileName << std::endl;
            debugToFile = true;

            mFile.open(fileName.c_str(), std::ios::app);
            time_t time            = std::time(0);
            std::string timeString = std::ctime(&time);

            mFile << "--------------------------------------------------------" << std::endl;
            mFile << "DEBUGGER STARTED: " << timeString << std::endl;
        } else {
            std::cout << "[CONSOLE]" << std::endl;
        }

        std::printf("\n");
    }
}

Debugger* Debugger::dbg = nullptr;

Debugger * Debugger::getInstance() {
    if (dbg == nullptr) {
        dbg = new Debugger();
    }
    return dbg;
}

void Debugger::log(const DEBUG_TYPE &type, int numArgs,...) {
    if (enableDebug) {
        va_list va;
        va_start(va, numArgs);
            for(int i =0; i != numArgs; i++) {
                char* arg = va_arg(va,char *);
                if (type == WARNING) {
                    if (debugToFile) {
                        write_to_file((char *)"WARNING:");
                        write_to_file(arg);
                    } else {
                        std::cerr << arg << std::endl;
                    }

                } else if (type == CRITICAL) {
                    if (debugToFile) {
                        write_to_file((char *)"CRITICAL:");
                        write_to_file(arg);
                    } else {
                        std::cerr << arg << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                } else if (type == LUA_VERBOSE) {
                    if(DEBUG_LUA_VERBOSE) {
                        if (debugToFile) {
                            write_to_file((char *)"LUA_VERBOSE:");
                            write_to_file(arg);
                        } else {
                            std::cout << arg << std::endl;
                        }
                    }
                } else {
                    if (debugToFile) {
                        write_to_file((char*)"VERBOSE:");
                        write_to_file(arg);
                    } else {
                        std::cout << arg << std::endl;
                    }
                }
            }
        va_end(va);

        if(type == CRITICAL) {
            time_t time            = std::time(0);
            std::string timeString = std::ctime(&time);

            if (debugToFile) {
                mFile << "DEBUGGER ENDED: " << timeString << std::endl;
                mFile << "--------------------------------------------------------" << std::endl;
                mFile.close();
            }

            std::exit(EXIT_FAILURE);
        }
    }
}

void Debugger::write_to_file(char * str) {
    mFile << str << std::endl;
    mFile.flush();
}

Debugger::~Debugger() {
    if (debugToFile) {
        mFile.close();
    }
}
