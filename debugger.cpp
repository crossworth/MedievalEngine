#include "debugger.h"

using namespace ME;

Debugger::Debugger() : debugToFile(false) , enableDebug(false)
{
    enableDebug = DEBUG;
    if ( enableDebug ){
        std::printf("Debug iniciado");

        if ( debugFile.size() > 0){
            std::cout << "(File) " << debugFile << std::endl;
            fileName = debugFile;
            debugToFile = true;
            mFile.open(fileName.c_str(),std::ios::app);
            time_t time = std::time(0);
            std::string timeString = std::ctime(&time);
            mFile << "--------------------------------------------------------" << std::endl;
            mFile << "Debug iniciado - " << timeString << std::endl;
        }else{
            std::printf("(Console)");
        }

        std::printf("\n");
    }
}

Debugger * Debugger::getInstance()
{
    static Debugger *dbg = new Debugger();
    return dbg;
}

void Debugger::log(const debug_type &type,int numArgs,...){
    if ( enableDebug ){
        va_list va;
        va_start(va,numArgs);
            for(int i =0; i != numArgs ;i ++){

                char* arg = va_arg(va,char *);
                if ( type == WARNING){
                    if ( debugToFile)
                        write_to_file(arg);
                    else
                        std::cout << arg << std::endl;

                }else if ( type == CRITICAL){
                    if ( debugToFile){
                        write_to_file((char *)"Critical:");
                        write_to_file(arg);
                    }else
                        std::cerr << arg << std::endl;

                }else{
                    if ( debugToFile){
                        write_to_file((char*)"Fatal:");
                        write_to_file(arg);
                    }else
                        std::cerr << arg << std::endl;

                    std::exit(EXIT_FAILURE);
                }
            }
        va_end(va);
    }
}

void Debugger::write_to_file(char * str){
    mFile << str << std::endl;
    mFile.flush();
}

Debugger::~Debugger(){

    if (  debugToFile )
        mFile.close();
}
