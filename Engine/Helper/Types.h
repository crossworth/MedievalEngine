#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <ctime>
#include <cstdio>
#include <cstdint>

namespace ME {

/**
 * @brief The FileEntry struct
 */
struct FileEntry {
    char name[300];   // The name of the file
    char fileLocation[FILENAME_MAX];  // The real location of the file (memory or disk path)
    std::uint64_t size;    // The size of the file
    std::uint64_t offset;  // Where in the final file the data is
};

/**
 * @brief The FileHeader struct
 */
struct FileHeader {
    char version[6];           // Version of the dat file
    char name[300];            // Name of the dat file
    char description[512];     // The description of the dat file
    std::uint32_t filesNumber;  // The number of files
    std::uint64_t createOn;    // When the file was created (time_t)
};

typedef char _BYTE;

#ifndef nullptr
#define nullptr NULL
#endif

}
#endif // FILEENTRY_H
