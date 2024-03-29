#include "DATFile.h"

using namespace ME;

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

bool DATFile::createFile(const std::string &outputFile,
                         const std::string &fileName,
                         const std::string &description) {

    std::ifstream inFile;
    std::ofstream outFile;

    byte buffer[1];

    std::memset(&mHeader, 0, sizeof(mHeader));

    std::memcpy(mHeader.name, fileName.c_str(),
                std::strlen(fileName.c_str()));

    std::memcpy(mHeader.version, VERSION.c_str(),
                std::strlen(VERSION.c_str()));

    std::memcpy(mHeader.description, description.c_str(),
                std::strlen(description.c_str()));

    mHeader.createOn    = static_cast<uint64>(time(0));
    mHeader.filesNumber = static_cast<uint32>(mFileEntry.size());

    for (uint32 i = 0; i < mFileEntry.size(); i++) {
        inFile.open(mFileEntry[i].fileLocation,
                    std::ifstream::in | std::ifstream::binary);

        if (inFile.is_open()) {
            inFile.seekg(0, std::ios::end);
            mFileEntry[i].size = inFile.tellg();
            inFile.close();
        } else {
            LOG << Log::WARNING << "[DATFile::createFile] Error while opening file: "
                      << mFileEntry[i].fileLocation << std::endl;
            mHeader.filesNumber = mHeader.filesNumber - 1;
            mFileEntry.erase(mFileEntry.begin() + i);
        }
    }

    uint64 offset = 0;
    offset += std::strlen(FILE_HEADER_TAG.c_str());
    offset += sizeof(FileHeader);
    offset += mHeader.filesNumber * sizeof(FileEntry);

    for (uint32 i = 0; i < mFileEntry.size(); i++) {
        mFileEntry[i].offset = offset;
        offset               = offset + mFileEntry[i].size;
    }

    if (mHeader.filesNumber <= 0) {
        LOG << Log::WARNING << "[DATFile::createFile] "
            << "You have to select at least one file" << std::endl;
        return false;
    }

    outFile.open(outputFile.c_str(),
                 std::ostream::out | std::ostream::binary);

    if (outFile.is_open()) {

        outFile.write(FILE_HEADER_TAG.c_str(), std::strlen(FILE_HEADER_TAG.c_str()));
        outFile.write((byte*)&mHeader, sizeof(FileHeader));

        std::unordered_map<std::string, std::string> realFileLocations;

        for (uint32 i = 0; i < mFileEntry.size(); i++) {
            realFileLocations[mFileEntry[i].name] = mFileEntry[i].fileLocation;
            std::memset(mFileEntry[i].fileLocation, 0, FILENAME_MAX);
            std::memcpy(mFileEntry[i].fileLocation, "memory", std::strlen("memory"));
            outFile.write((byte*)&mFileEntry[i], sizeof(FileEntry));
        }

        for (uint32 i = 0; i < mFileEntry.size(); i++) {

            if (realFileLocations.find(mFileEntry[i].name) !=
               realFileLocations.end()) {

                inFile.open(realFileLocations[mFileEntry[i].name].c_str(),
                            std::ifstream::in | std::ifstream::binary);

                if (inFile.is_open()) {
                    inFile.seekg(0, std::ios::beg);
                    while (inFile.read(buffer, 1)) {
                        outFile.write(buffer, 1);
                    }
                    inFile.close();
                }
                inFile.clear();
            } else {
                LOG << Log::WARNING << "[DATFile::createFile] "
                    <<  "File not found on the realFileLocations map" << std::endl;
            }
        }

        mCurrentFile = outputFile;
        outFile.close();
        return true;
    } else {
        LOG << Log::WARNING << "[DATFile::createFile] "
            << "Error while creating the output file" << std::endl;
        return false;
    }
}

bool DATFile::openFile(const std::string &fileName) {
    std::ifstream inFile;

    FileEntry fileEntry;

    std::memset(&mHeader, 0, sizeof(FileHeader));

    inFile.open(fileName.c_str(),
                std::ifstream::in | std::ifstream::binary);

    if (inFile.is_open()) {
        char headerTAG[FILE_HEADER_TAG_SIZE];

        inFile.seekg(0, std::ios::beg);
        inFile.read(headerTAG, FILE_HEADER_TAG_SIZE);
        inFile.read((byte*)&mHeader, sizeof(FileHeader));

        LOG << Log::WARNING << "[DATFile::openFile] "
            << "Number of files (DAT): " << mHeader.filesNumber
            << std::endl;

        if (mHeader.filesNumber > ME_MAX_DAT_FILES) {
            LOG << Log::WARNING << "[DATFile::openFile] "
                << "Error while opening the file " + fileName
                << " number of files exceeds " << ME_MAX_DAT_FILES
                << std::endl;

            inFile.close();
            return false;
        }

        for (uint32 i = 0; i < mHeader.filesNumber; i++) {
            inFile.read((byte*)&fileEntry, sizeof(FileEntry));
            mFileEntry.push_back(fileEntry);
        }
        inFile.close();
        mCurrentFile = fileName;
        return true;
    } else {
        LOG << Log::WARNING << "[DATFile::openFile] "
            << "Error while opening the file " + fileName << std::endl;
        return false;
    }
}

bool DATFile::isFileOpen() {
    if (mCurrentFile.empty()) {
        LOG << Log::WARNING << "[DATFile::isFileOpen] "
            << "You have to open a file first" << std::endl;
        return false;
    }

    return true;
}

std::string DATFile::getName() {
    if (!isFileOpen()) {
        return "";
    }

    return std::string(mHeader.name);
}

std::string DATFile::getVersion() {
    if (!isFileOpen()) {
        return "";
    }

    return std::string(mHeader.version);
}

std::string DATFile::getDescription() {
    if (!isFileOpen()) {
        return "";
    }

    return std::string(mHeader.description);
}

uint64 DATFile::getDate() {
    if (!isFileOpen()) {
        return 0;
    }

    return mHeader.createOn;
}

void DATFile::addFileEntry(const std::string &fileLocation,
                           const std::string &fileName) {
    FileEntry fileEntry;
    std::memset(&fileEntry, 0, sizeof(FileEntry));
    std::memcpy(fileEntry.name, fileName.c_str(), std::strlen(fileName.c_str()));
    std::memcpy(fileEntry.fileLocation, fileLocation.c_str(),
                std::strlen(fileLocation.c_str()));

    fileEntry.offset = 0;
    fileEntry.size   = 0;
    mFileEntry.push_back(fileEntry);
}

byte* DATFile::getFile(const std::string &fileEntryName) {
    if (!isFileOpen()) {
        return static_cast<byte*>(nullptr);
    }

    std::ifstream inFile;

    if (mBuffer) {
        delete mBuffer;
        mBuffer = nullptr;
    }

    for (uint32 i = 0; i < mHeader.filesNumber; i++) {
        if (std::strcmp(mFileEntry[i].name, fileEntryName.c_str()) == 0) {

            mBuffer = new byte[mFileEntry[i].size];

            if (mBuffer == nullptr) {
                return nullptr;
            }

            inFile.open(mCurrentFile.c_str(),
                        std::ifstream::in | std::ifstream::binary);

            if (inFile.is_open()) {
                inFile.seekg(mFileEntry[i].offset, std::ios::beg);
                inFile.read(mBuffer, mFileEntry[i].size);
                inFile.close();
                return mBuffer;
            }
        }
    }
    return new char;
}

void DATFile::removeFile(const std::string &fileEntryName) {
    if (!isFileOpen()) {
        return;
    }

    for (uint32 i = 0; i < mHeader.filesNumber; i++) {
        if (std::strcmp(mFileEntry[i].name, fileEntryName.c_str()) == 0) {
            mFileEntry.erase(mFileEntry.begin() + i);
            mHeader.filesNumber--;
            break;
        }
    }

}

std::vector<std::string> DATFile::getFileList() {
    if (!isFileOpen()) {
        return std::vector<std::string>();
    }
    std::vector<std::string> returnVector;

    for (uint32 i = 0; i < mFileEntry.size(); i++) {
        returnVector.push_back(std::string(mFileEntry[i].name));
    }

    return returnVector;
}

uint32 DATFile::getFileEntrySize(const std::string &fileEntryName) {
    for (uint32 i = 0; i < mHeader.filesNumber; i++) {
        if (std::strcmp(mFileEntry[i].name, fileEntryName.c_str()) == 0) {
            return mFileEntry[i].size;
        }
    }
    return 0;
}
