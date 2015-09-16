#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <ctime>
#include <cstdio>
#include <cstdint>
#include <functional>
#include <memory>



/**
 * Define an empty void lambda function <br>
 * NOTE(Pedro): Since we are using lambda functions, we require C++11<br>
 */
#define EMPTY_VOID_CALLBACK [] (void) {}

namespace ME {


class Effect;
class Window;
class Widget;
class TextWidget;
class TextListWidget;
class GUIEvent;
class ButtonWidget;


/**
 * One byte variable type
 */
typedef char MEByte;

/**
 * int 32 variable type
 */
typedef std::int32_t MEInt32;

/**
 * unsigned int 32 variable type
 */
typedef std::uint32_t MEUInt32;

/**
 * int 64 variable type
 */
typedef std::int64_t MEInt64;

/**
 * unsigned int 64 variable type
 */
typedef std::uint64_t MEUInt64;

/**
 * The ME::ResourceID type used on all the ME::Resource and ME::ResourceManager
 */
typedef unsigned long int ResourceID;

/**
 * Define the ME::WidgetPtr with a shared pointer to a ME::Widget
 */
typedef std::shared_ptr<Widget> WidgetPtr;

/**
 * Define the ME::VoidCallback with a function pointer
 */
typedef std::function<void(void)> VoidCallback;

/**
 * Define the ME::WidgetCallback with a function pointer
 */
typedef std::function<void(Widget*)> WidgetCallback;

/**
 * Define the ME::EffectPtr with a shared pointer to a ME::Effect
 */
typedef std::shared_ptr<Effect> EffectPtr;

/**
 * Define the ME::TextWdigetPtr with a shared pointer to a ME::TextWidget
 */
typedef std::shared_ptr<TextWidget> TextWidgetPtr;

/**
 * Define the TextListWidgetPtr with a shared pointer to a ME::TextListWidget
 */
typedef std::shared_ptr<TextListWidget> TextListWidgetPtr;

/**
 * Define the ME::GUIEVentPtr with a shared pointer to a ME::GUIEvent
 */
typedef std::shared_ptr<GUIEvent> GUIEventPtr;

/**
 * Define the ME::ButtonWidgetPtr with a shared pointer to a ME::ButtonWidget
 */
typedef std::shared_ptr<ButtonWidget> ButtonWidgetPtr;


/**
 * Max file name<br>
 * We use this on the ME::DATFile <br>
 * <br>
 * NOTE(Pedro): FILENAME_MAX is 260 on Windows and 1024 on MacOSX<br>
 * So we have to use our own version of FILE_NAME_MAX<br>
 * We set it to 255 since it's a comum value on Window and MacOS<br>
 */
const MEInt32 ME_MAX_FILE_NAME = 255;

/**
 * Max number of files on a ME::DATFile
 */
const MEInt32 ME_MAX_DAT_FILES = 10000;

/**
 * @brief The ME::FileEntry struct used on the ME::DATFile
 */
struct FileEntry {
    char name[300];  ///< The name of the file
    char fileLocation[ME_MAX_FILE_NAME];  ///< The real location of the file (memory or disk path)
    MEInt64 size;    ///< The size of the file
    MEInt64 offset;  ///< Where in the final file the data is
};

/**
 * @brief The ME::FileHeader struct used on the ME::DATFile
 */
struct FileHeader {
    char version[6];       ///< Version of the dat file
    char name[300];        ///< Name of the dat file
    char description[512]; ///< The description of the dat file
    MEInt32 filesNumber;   ///< The number of files
    MEInt64 createOn;      ///< When the file was created (time_t)
};

}


#endif // FILEENTRY_H
