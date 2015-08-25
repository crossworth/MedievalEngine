#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <ctime>
#include <cstdio>

namespace SM {

/**
 * @brief The FileEntry struct
 */
struct FileEntry {
    char name[300];   // The name of the file
    char realFileName[FILENAME_MAX];  // The real path of file
    long int size;    // The size of the file
    long int offSet;  // Where in the final file the data is
};

/**
 * @brief The FileHeader struct
 */
struct FileHeader {
    char version[6];           // Version of the dat file
    char name[300];            // Name of the dat file
    char description[512];     // The description of the dat file
    unsigned int numberFiles;  // The number of files
    long long int createOn;    // When the file was created (time_t)
};

typedef char BYTE;

#ifndef nullptr
#define nullptr NULL
#endif

}
#endif // FILEENTRY_H
