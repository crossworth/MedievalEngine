#include "DATFile.h"

using namespace SM;

DATFile::DATFile() {
    mBuffer      = nullptr;
    mCurrentFile = "";
}

DATFile::~DATFile() {
    if (mBuffer) {
        delete mBuffer;
        mBuffer = nullptr;
    }
}

bool DATFile::createFile(const std::string& outputFile, const std::string& fileName, const std::string& description) {

    std::ifstream inFile;
    std::ofstream outFile;

    BYTE buffer[1];
    FileEntry tmp;

    std::memset(&mHeader, 0, sizeof(mHeader));

    std::memcpy(mHeader.name, fileName.c_str(), std::strlen(fileName.c_str()));
    std::memcpy(mHeader.version, "1.0", 3);
    std::memcpy(mHeader.description, description.c_str(), std::strlen(description.c_str()));

    mHeader.createOn    = static_cast<long long int>(time(0));
    mHeader.numberFiles = mFileEntry.size();

    for (unsigned int i = 0; i < mFileEntry.size(); i++) {
        inFile.open(mFileEntry[i].realFileName, std::ifstream::in | std::ifstream::binary);

        if (inFile.is_open() || std::string(mFileEntry[i].realFileName) == std::string("memory")) {
            inFile.seekg(0, std::ios::end);
            std::memset(mFileEntry[i].realFileName, 0, sizeof(char) * FILENAME_MAX);
            std::memcpy(mFileEntry[i].realFileName, "memory", std::strlen("memory"));
            mFileEntry[i].size = inFile.tellg();
            inFile.close();
        } else {
            std::cerr << "Error while opening file: " << mFileEntry[i].realFileName << std::endl;
            mHeader.numberFiles = mHeader.numberFiles - 1;
            mFileEntry.erase(mFileEntry.begin() + i);
        }
    }

    long int offSet = 0;
    offSet += std::strlen(FILE_HEADER_TAG.c_str());
    offSet += sizeof(FileHeader);
    offSet += mHeader.numberFiles * sizeof(FileEntry);

    for (unsigned int i=0; i < mFileEntry.size(); i++) {
        mFileEntry[i].offSet = offSet;
        offSet               = offSet + mFileEntry[i].size;
    }

    if (mHeader.numberFiles <= 0) {
        std::cerr << "You have to select at least one file" << std::endl;
        return false;
    }

    int pos                 = outputFile.rfind(".dat");
    std::string tmpFileName = outputFile.substr(0, pos);

    outFile.open((tmpFileName + FILE_EXTENSION).c_str(), std::ostream::out | std::ostream::binary);

    if (outFile.is_open()) {

        outFile.write(FILE_HEADER_TAG.c_str(), std::strlen(FILE_HEADER_TAG.c_str()));
        outFile.write((BYTE*)&mHeader, sizeof(FileHeader));

        for (unsigned int i = 0; i < mFileEntry.size(); i++) {
            outFile.write((BYTE*)&mFileEntry[i], sizeof(FileEntry));
        }

        for (unsigned int i = 0; i < mFileEntry.size(); i++) {
            inFile.open(mFileEntry[i].realFileName, std::ifstream::in | std::ifstream::binary);
            if (inFile.is_open()) {
                inFile.seekg(0, std::ios::beg);
                while (inFile.read(buffer, 1)) {
                    outFile.write(buffer, 1);
                }
                inFile.close();
            }
            inFile.clear();
        }

        mCurrentFile = fileName;
        outFile.close();
        return true;
    } else {
        std::cerr << "Error while creating the output file" << std::endl;
        return false;
    }
}

bool DATFile::openFile(const std::string& fileName) {
    std::ifstream inFile;

    FileEntry tmp;

    std::memset(&mHeader, 0, sizeof(FileHeader));

    int pos  = fileName.rfind(".dat");
    std::string tmpFileName = fileName.substr(0, pos);

    inFile.open((tmpFileName + FILE_EXTENSION).c_str(), std::ifstream::in | std::ifstream::binary);

    if (inFile.is_open()) {
        int tagLength = std::strlen(FILE_HEADER_TAG.c_str());
        char headerTAG[tagLength];

        inFile.seekg(0, std::ios::beg);
        inFile.read(headerTAG, tagLength);
        inFile.read((BYTE*)&mHeader, sizeof(FileHeader));

        for (unsigned int i = 0; i < mHeader.numberFiles; i++) {
            inFile.read((BYTE*)&tmp, sizeof(FileEntry));
            mFileEntry.push_back(tmp);
        }
        inFile.close();
        mCurrentFile = tmpFileName;
        return true;
    } else {
        std::cerr << "Error while opening the file " + tmpFileName << std::endl;
        return false;
    }
}

std::string DATFile::getName() {
    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return "";
    }
    return std::string(mHeader.name);
}

std::string DATFile::getVersion() {
    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return "";
    }
    return std::string(mHeader.version);
}

std::string DATFile::getDescription() {
    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return "";
    }
    return std::string(mHeader.description);
}

long long int DATFile::getDate() {
    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return 0;
    }
    return mHeader.createOn;
}

void DATFile::addFileEntry(const std::string& fileLocation, const std::string& fileName) {
    FileEntry fileEntry;
    std::memset(&fileEntry, 0, sizeof(FileEntry));
    std::memcpy(fileEntry.name, fileName.c_str(), std::strlen(fileName.c_str()));
    std::memcpy(fileEntry.realFileName, fileLocation.c_str(), std::strlen(fileLocation.c_str()));
    fileEntry.offSet = 0;
    fileEntry.size   = 0;
    mFileEntry.push_back(fileEntry);
}

BYTE* DATFile::getFile(const std::string& fileEntryName) {

    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return static_cast<BYTE*>(nullptr);
    }

    std::ifstream inFile;

    if (mBuffer) {
        delete mBuffer;
        mBuffer = nullptr;
    }

    for (unsigned int i = 0; i < mHeader.numberFiles; i++) {
        if (std::strcmp(mFileEntry[i].name, fileEntryName.c_str()) == 0) {

            mBuffer = new BYTE[mFileEntry[i].size];

            if (mBuffer == nullptr) {
                return nullptr;
            }

            inFile.open((mCurrentFile + FILE_EXTENSION).c_str(), std::ifstream::in | std::ifstream::binary);

            if (inFile.is_open()) {
                inFile.seekg(mFileEntry[i].offSet, std::ios::beg);
                inFile.read(mBuffer, mFileEntry[i].size);
                inFile.close();
                return mBuffer;
            }
        }
    }
    return new char;
}

void DATFile::removeFile(const std::string& fileEntryName) {
    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < mHeader.numberFiles; i++) {
        if (std::strcmp(mFileEntry[i].name, fileEntryName.c_str()) == 0) {
            mFileEntry.erase(mFileEntry.begin() + i);
            mHeader.numberFiles--;
            break;
        }
    }

}

std::vector<std::string> DATFile::getFileList() {
    if (mCurrentFile.empty()) {
        std::cerr << "YOU HAVE TO OPEN A FILE FIRST" << std::endl;
        return std::vector<std::string>();
    }
    std::vector<std::string> returnVector;

    for (unsigned int i = 0; i < mFileEntry.size(); i++) {
        returnVector.push_back(std::string(mFileEntry[i].name));
    }

    return returnVector;
}

long int DATFile::getFileEntrySize(const std::string& fileEntryName) {
    for (unsigned int i = 0; i < mHeader.numberFiles; i++) {
        if (std::strcmp(mFileEntry[i].name, fileEntryName.c_str()) == 0) {
            return mFileEntry[i].size;
        }
    }
    return 0;
}

