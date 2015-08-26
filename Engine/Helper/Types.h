#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <ctime>
#include <cstdio>

namespace ME {

/**
 * @brief The FileEntry struct
 */
struct FileEntry {
    char name[300];   // The name of the file
    char fileLocation[FILENAME_MAX];  // The real location of the file (memory or disk path)
    long int size;    // The size of the file
    long int offset;  // Where in the final file the data is
};

/**
 * @brief The FileHeader struct
 */
struct FileHeader {
    char version[6];           // Version of the dat file
    char name[300];            // Name of the dat file
    char description[512];     // The description of the dat file
    unsigned int filesNumber;  // The number of files
    long long int createOn;    // When the file was created (time_t)
};

typedef char BYTE;

#ifndef nullptr
#define nullptr NULL
#endif

}
#endif // FILEENTRY_H
