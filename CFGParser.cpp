#include "CFGParser.h"

using namespace ME;

CFGParser::CFGParser() {
    dbg = Debugger::getInstance();
}

void CFGParser::readFile(const std::string &configFile) {

    this->fileName = configFile;

    std::fstream file;
    file.open(configFile.c_str(), std::ios::out | std::ios::in);
    if (file.is_open()) {
      std::string line;
      while(!file.eof()) {
          std::getline(file, line);

         if (validateLine(line)) {
             std::string tmpKey, tmpValue;
             tmpKey           = mGetKey(line);
             tmpValue         = mGetValue(line);
             contents[tmpKey] = tmpValue;
         }
      }
       file.close();
    } else {
        dbg->log(WARNING, 1, ("[CFGParser::readFile] Configuration file (" + this->fileName + ") not found").c_str());
    }
}


void CFGParser::clear() {
    contents.clear();
}

void CFGParser::saveFile(const std::string &configFile){
    std::ofstream outFile;
    outFile.open(configFile.c_str(), std::ios::out);

    if (outFile.is_open()) {
        outFile << "# " << ENGINE_DEFAULTS::ENGINE_NAME << " Version: " << ENGINE_DEFAULTS::ENGINE_VERSION << " - CFGParser" << std::endl;

        std::map<std::string, std::string>::iterator it = contents.begin();

        while(it != contents.end()) {
            outFile << it->first << "=" << it->second << std::endl;
            it++;
        }

        outFile.close();
    } else {
         dbg->log(CRITICAL, 1, ("[CFGParser::saveFile] Could not create Configuration file (" + this->fileName + ")").c_str());
    }
}


bool CFGParser::add(std::string key, std::string value) {
    contents[key] =  value;
    return true;
}

bool CFGParser::keyExists(std::string &key) {
    std::map<std::string, std::string>::iterator it;
    it = contents.find(key);
    if (it != contents.end()) {
        return true;
    } else {
        return false;
    }
}

std::string CFGParser::getKey(std::string key) {
    if (keyExists(key)) {
        return contents[key];
    } else {
        dbg->log(WARNING, 1,("[CFGParser::getKey] Key (" + key + ") not found").c_str());
    }
    return "";
}



CFGParser::CFGParser(const std::string &configFile) {
    dbg = Debugger::getInstance();
    this->readFile(configFile);
}

bool CFGParser::validateLine(std::string &line){
    if (line.empty()) {
        return false;
    }

    // Remove os espaços em branco no começo
    int pos = line.find_first_not_of("\t ");


    // Erro de uma unica tabulaçao na linha
    if(pos < 0) {
        return false;
    }

    line = line.substr(pos, line.size());

    // Remove comentário
    pos = line.find_first_of("#");

    // somente se encontrar comentario
    if (pos >=0) {
       line = line.substr(0, pos);
    }

    // Remove os espaços em branco no final
    pos  = line.find_last_not_of("\t ");
    line = line.substr(0, pos+1);

    // Verifica se o igual esta na posição correta
    if (  line.find("=") <= 0 || line.find("=") >= line.size()-1) {
        return false;
    }

    return true;
}



std::string CFGParser::mGetKey(std::string line) {
    signed int pos = line.find("=");

    line =  line.substr(0, pos);
    pos  = line.find(" ");
    if (pos != (signed int)std::string::npos) {
        line = line.substr(0,pos);
    }
    return line;
}

std::string CFGParser::mGetValue(std::string line) {
    int pos = line.find("=");
    return line.substr(pos+1, line.size());
}
