#include "cfgparser.h"

using namespace ME;

CFGParser::CFGParser()
{
    dbg = Debugger::getInstance();
}

void CFGParser::readFile(const std::string &configFile){

    this->fileName = configFile;

    std::fstream file;
    file.open(configFile.c_str(), std::ios_base::out | std::ios_base::in);  // will not create file
    if (file.is_open())
    {
      std::string line;
      while(!file.eof()){
          std::getline(file,line);

         if ( validateLine(line) ){
             std::string tmpKey,tmpValue;
             tmpKey = mGetKey(line);
             tmpValue = mGetValue(line);
             contents[tmpKey] = tmpValue;
         }
      }
       file.close();
    }else{
        dbg->log(CRITICAL,1,"Cfg file not found");
    }
}


void CFGParser::clear(){
    contents.clear();
}

void CFGParser::saveFile(const std::string &configFile){
    std::ofstream outFile;
    outFile.open(configFile.c_str(),std::ios::out);

    if ( outFile.is_open()){
        outFile << "#Gerado automaticamente pelo CFGParser" << std::endl;

        std::map<std::string,std::string>::iterator it = contents.begin();

        while(it != contents.end()){
            outFile << it->first << "=" << it->second << std::endl;
            it++;
        }

    }else{
         dbg->log(CRITICAL,1,"Could not create the cfg file");
    }
    outFile.close();
}


bool CFGParser::add(std::string key,std::string value){

    contents[key] =  value;
    return true;
}

bool CFGParser::keyExists(std::string &key){
    std::map<std::string,std::string>::iterator it;
    it = contents.find(key);
    if (  it != contents.end())
        return true;
    else
        return false;
}


CFGParser::CFGParser(const std::string &configFile){
    dbg = Debugger::getInstance();

    this->fileName = configFile;

    std::fstream file;
    file.open(configFile.c_str(), std::ios_base::out | std::ios_base::in);  // will not create file
    if (file.is_open())
    {
      std::string line;
      int lineCounter = 0;
      while(!file.eof()){
          std::getline(file,line);

         if ( validateLine(line) ){
             std::string tmpKey,tmpValue;
             tmpKey = mGetKey(line);
             tmpValue = mGetValue(line);
             if ( keyExists(tmpKey)){
                 std::string tmpCounter = Converter::T_to_string<int>(lineCounter);
                 dbg->log(CRITICAL,1,("Key duplicate in the configFile:" +configFile + " Keyname: " +tmpKey + " on line: " + tmpCounter).c_str());
             }else{
                contents[tmpKey] = tmpValue;
             }
             lineCounter++;
         }
      }
       file.close();
    }else{
        dbg->log(CRITICAL,1,"Cfg file not found");
    }

}

bool CFGParser::validateLine(std::string &line){
    if ( line.empty() )
        return false;

    // remove white space at beginner
    int pos = line.find_first_not_of("\t ");


    // erro de uma unica tabulacao na linha
    if(  pos < 0)
        return false;

    line = line.substr(pos,line.size());


    // remove comments
    pos = line.find_first_of("#");
    // somente se encontrar comentario
    if ( pos >=0 )
       line = line.substr(0,pos);

    //remove white space at end
    pos = line.find_last_not_of("\t ");
    line = line.substr(0,pos+1);

    //valida se o igual esta na posicao certa
    if (  line.find("=") <= 0 || line.find("=") >= line.size()-1)
        return false;

    return true;
}



std::string CFGParser::mGetKey(std::string line){
    signed int pos = line.find("=");

    line =  line.substr(0,pos);
    pos = line.find(" ");
    if ( pos != (signed int)std::string::npos){
        line = line.substr(0,pos);
    }
    return line;
}
std::string CFGParser::mGetValue(std::string line){
    int pos = line.find("=");
    return line.substr(pos+1,line.size());
}
