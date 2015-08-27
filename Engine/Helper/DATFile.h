#ifndef DATFILE_H
#define DATFILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include "LogInc.h"
#include "Helper/Types.h"

namespace ME {

const std::string VERSION         = "1.0.0";
const std::string FILE_EXTENSION  = ".dat";
const std::string FILE_HEADER_TAG = "MEDIEVALENGINE_FILE";

class DATFile {
public:
    DATFile();
    ~DATFile();

    bool createFile(const std::string& fileName,
                    const std::string& outputFile,
                    const std::string& description);

    bool openFile(const std::string& fileName);
    std::string getName();
    std::string getVersion();
    std::string getDescription();

    std::uint64_t getDate();

    void addFileEntry(const std::string& fileLocation,
                      const std::string& fileName);

    _BYTE* getFile(const std::string& fileEntryName);
    void removeFile(const std::string& fileEntryName);
    std::vector<std::string> getFileList();
    std::uint64_t getFileEntrySize(const std::string& fileEntryName);

private:
    bool isFileOpen();
    FileHeader mHeader;
    std::vector<FileEntry> mFileEntry;
    std::string mCurrentFile;
    _BYTE* mBuffer;
};

}

#endif // DATFILE_H
