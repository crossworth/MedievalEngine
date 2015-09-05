#include "CFGParser.h"

using namespace ME;

CFGParser::CFGParser() {

}

void CFGParser::readFile(const std::string& configFile) {

    this->mFileName = configFile;

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
             mContents[tmpKey] = tmpValue;
         }
      }
       file.close();
    } else {
        LOG << Log::WARNING
            << ("[CFGParser::readFile] Configuration file (" + this->mFileName + ") not found").c_str()
            << std::endl;
    }
}

void CFGParser::clear() {
    mContents.clear();
}

void CFGParser::saveFile(const std::string& configFile){
    std::ofstream outFile;
    outFile.open(configFile.c_str(), std::ios::out);

    if (outFile.is_open()) {
        outFile << "# " << ENGINE_DEFAULTS::ENGINE_NAME
                << " Version: " << ENGINE_DEFAULTS::ENGINE_VERSION
                << " - CFGParser" << std::endl;

        std::map<std::string, std::string>::iterator it = mContents.begin();

        while(it != mContents.end()) {
            outFile << it->first << "=" << it->second << std::endl;
            it++;
        }

        outFile.close();
    } else {
        LOG << Log::WARNING
            << ("[CFGParser::saveFile] Could not save Configuration file (" + this->mFileName + ")" ).c_str()
            << std::endl;
    }
}

bool CFGParser::add(std::string key, std::string value) {
    mContents[key] =  value;
    return true;
}

bool CFGParser::keyExists(std::string& key) {
    std::map<std::string, std::string>::iterator it;
    it = mContents.find(key);
    if (it != mContents.end()) {
        return true;
    } else {
        return false;
    }
}

std::string CFGParser::getKey(std::string key) {
    if (keyExists(key)) {
        return mContents[key];
    } else {
        LOG << Log::WARNING
            << ("[CFGParser::getKey] Key (" + key + ") not found").c_str()
            << std::endl;
    }
    return "";
}

CFGParser::CFGParser(const std::string& configFile) {
    this->readFile(configFile);
}

std::map<std::string, std::string> CFGParser::getContents() {
    return mContents;
}

bool CFGParser::validateLine(std::string& line){
    if (line.empty()) {
        return false;
    }

    // Remove os espaços em branco no começo
    size_t pos = line.find_first_not_of("\t ");

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
    size_t pos = line.find("=");

    line = line.substr(0, pos);
    pos  = line.find(" ");
    if (pos != (signed int)std::string::npos) {
        line = line.substr(0,pos);
    }
    return line;
}

std::string CFGParser::mGetValue(std::string line) {
    size_t pos         = line.find("=");
    std::string result = line.substr(pos+1, line.size());


    // trim
    size_t first = result.find_first_not_of("\t ");
    size_t last = result.find_last_not_of(' ');
    result = result.substr(first, (last-first+1));

    // Fix \n in file not been reconized
    std::string::size_type posNewLine = 0;
    while ((posNewLine = result.find("\\n", posNewLine)) != std::string::npos) {
        result.replace(posNewLine, 2, " \n");
    }

    return result;
}
