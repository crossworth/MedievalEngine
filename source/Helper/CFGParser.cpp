#include "CFGParser.h"

using namespace ME;

CFGParser::CFGParser() {

}

void CFGParser::readFile(const std::string& configFile) {
    // Store the configuration file name
    this->mFileName = configFile;

    // configuration file input
    std::fstream file;
    // try to open the file
    file.open(configFile.c_str(), std::ios::out | std::ios::in);
    // if we can open the file
    if (file.is_open()) {
        // our buffer string
        std::string line;

        // while we are not on the end of the file
        while(!file.eof()) {
            // read the line
            std::getline(file, line);

            // validate the line
            if (validateLine(line)) {

                // store the line on the content
                std::string tmpKey, tmpValue;
                tmpKey           = mGetKey(line);
                tmpValue         = mGetValue(line);


                // if we are loading an array
                // first verify we have found empty brackts
                // and get the position
                size_t arrayPos  = tmpKey.find_last_of("[]");

                // if we have found
                if (arrayPos != std::string::npos) {
                    // current index set to zero
                    int currentIndex = 0;

                    // loop through all the elements lookin for the key
                    for(auto it = mContents.begin(); it != mContents.end(); it++) {
                        std::string keyName;

                        // create the key name for look for
                        // in this case NAME_ar_1 or NAME_ar_2
                        keyName = tmpKey.substr(0, arrayPos - 1);
                        keyName = keyName + "_ar_" + std::to_string(currentIndex);

                        // if we found we increment the index
                        if (mContents.find(keyName) != mContents.end()){
                            currentIndex++;
                        }
                    }

                    // and finally create the correct name
                    tmpKey = tmpKey.substr(0, arrayPos - 1);
                    tmpKey = tmpKey + "_ar_" + std::to_string(currentIndex);
                }

                mContents[tmpKey] = tmpValue;
            }
        }
        // close the file
        file.close();
    } else {
        // TODO(Pedro): Use the new log method
        LOG << Log::WARNING
            << "[CFGParser::readFile] Configuration file (" + this->mFileName + ") not found"
            << std::endl;
    }
}

void CFGParser::clear() {
    mContents.clear();
}

void CFGParser::saveFile(const std::string& configFile){
    // configuration file output
    std::ofstream outFile;
    // try to open the file
    outFile.open(configFile.c_str(), std::ios::out);
    // if we can open the file
    if (outFile.is_open()) {
        // sample engine header
        outFile << "# " << ENGINE_DEFAULTS::ENGINE_NAME
                << " Version: " << ENGINE_DEFAULTS::ENGINE_VERSION
                << " - CFGParser" << std::endl;

        std::map<std::string, std::string>::iterator it = mContents.begin();

        while(it != mContents.end()) {
            // write all the lines to the file
            outFile << it->first << "=" << it->second << std::endl;
            it++;
        }
        // close the file
        outFile.close();
    } else {
        // TODO(Pedro): Use the new log method
        LOG << Log::WARNING
            << "[CFGParser::saveFile] Could not save Configuration file (" + this->mFileName + ")" 
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
        // TODO(Pedro): Use the new log method
        LOG << Log::WARNING
            << "[CFGParser::getKey] Key (" + key + ") not found"
            << std::endl;
    }
    // if we dont find the key we just return an empty string
    return "";
}

CFGParser::CFGParser(const std::string& configFile) {
    this->readFile(configFile);
}

std::map<std::string, std::string> CFGParser::getContents() {
    return mContents;
}

bool CFGParser::validateLine(std::string& line){
    // if the line is empty we just return
    if (line.empty()) {
        return false;
    }

    // remove all the spaces and tab from the start
    size_t pos = line.find_first_not_of("\t ");

    // error if we had only one tab on the line
    if(pos < 0) {
        return false;
    }

    // remove the tab
    line = line.substr(pos, line.size());

    // try find the comment
    pos = line.find_first_of("#");

    // we just remove the comment until the end
    // so we can put a comment on a line
    if (pos >= 0) {
       line = line.substr(0, pos);
    }

    // Remove the space at the end as well
    pos  = line.find_last_not_of("\t ");
    line = line.substr(0, pos + 1);

    // verify if  the equals is on the right position
    // if start with equals or it's at end we just return false
    if (line.find("=") <= 0 || line.find("=") >= line.size() - 1) {
        return false;
    }

    // else everything is ok
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
