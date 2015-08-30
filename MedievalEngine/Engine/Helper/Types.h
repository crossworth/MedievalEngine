#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <ctime>
#include <cstdio>
#include <cstdint>
#include <functional>


// NOTE(Pedro): FILENAME_MAX is 260 on Windows and 1024 on MacOSX
// So We have to use our own version of FILE_NAME_MAX

// NOTE(Pedro): Since We are using lambda functions, We require C++11
// Since #define is a preprocessor We can use this Way (where it's don't know about the class yet)
#define EMPTY_VOID_CALLBACK [](void) {}

namespace ME {

class Widget;

typedef char MEByte;

typedef std::int32_t MEInt32;
typedef std::uint32_t MEUInt32;

typedef std::int64_t MEInt64;
typedef std::uint64_t MEUInt64;

typedef std::function<void(void)> VoidCallback;
typedef std::function<void(Widget*)> WidgetCallback;

const MEInt32 ME_MAX_FILE_NAME = 255;
const MEInt32 ME_MAX_DAT_FILES = 10000;
/**
 * @brief The FileEntry struct
 */
struct FileEntry {
    char name[300];  // The name of the file
    char fileLocation[ME_MAX_FILE_NAME];  // The real location of the file (memory or disk path)
    MEInt64 size;    // The size of the file
    MEInt64 offset;  // Where in the final file the data is
};

/**
 * @brief The FileHeader struct
 */
struct FileHeader {
    char version[6];       // Version of the dat file
    char name[300];        // Name of the dat file
    char description[512]; // The description of the dat file
    MEInt32 filesNumber;   // The number of files
    MEInt64 createOn;      // When the file was created (time_t)
};





#ifndef nullptr
#define nullptr NULL
#endif

}
#endif // FILEENTRY_H
