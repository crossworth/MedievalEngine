#ifndef DATFILE_H
#define DATFILE_H
#include <unordered_map>
#include <cstring>
#include "LogInc.h"
#include "Helper/Types.h"

namespace ME {

/**
 * Max file name<br>
 * We use this on the ME::DATFile <br>
 * <br>
 * NOTE(Pedro): FILENAME_MAX is 260 on Windows and 1024 on MacOSX<br>
 * So we have to use our own version of FILE_NAME_MAX<br>
 * We set it to 255 since it's a comum value on Window and MacOS<br>
 */
const uint8 ME_MAX_FILE_NAME = 255;

/**
 * Max number of files on a ME::DATFile
 */
const uint32 ME_MAX_DAT_FILES = 100000;

/**
 * @brief The ME::FileEntry struct used on the ME::DATFile
 */
struct FileEntry {
    char name[300];  ///< The name of the file
    char fileLocation[ME_MAX_FILE_NAME];  ///< The real location of the file (memory or disk path)
    uint64 size;    ///< The size of the file
    uint64 offset;  ///< Where in the final file the data is
};

/**
 * @brief The ME::FileHeader struct used on the ME::DATFile
 */
struct FileHeader {
    char version[6];       ///< Version of the dat file
    char name[300];        ///< Name of the dat file
    char description[512]; ///< The description of the dat file
    uint32 filesNumber;    ///< The number of files
    uint64 createOn;       ///< When the file was created (time_t)
};


const std::string VERSION         = "1.0.0";
const std::string FILE_EXTENSION  = ".dat";
const std::string FILE_HEADER_TAG = "MEDIEVALENGINE_FILE";
const uint8 FILE_HEADER_TAG_SIZE  = 19;


class DATFile {
public:
    DATFile();
    ~DATFile();

    bool createFile(const std::string &fileName,
                    const std::string &outputFile,
                    const std::string &description);

    bool openFile(const std::string &fileName);
    std::string getName();
    std::string getVersion();
    std::string getDescription();

    uint64 getDate();

    void addFileEntry(const std::string &fileLocation,
                      const std::string &fileName);

    byte* getFile(const std::string &fileEntryName);
    void removeFile(const std::string &fileEntryName);
    std::vector<std::string> getFileList();
    uint32 getFileEntrySize(const std::string &fileEntryName);

private:
    bool isFileOpen();
    FileHeader mHeader;
    std::vector<FileEntry> mFileEntry;
    std::string mCurrentFile;
    byte *mBuffer;
};

}

#endif // DATFILE_H
