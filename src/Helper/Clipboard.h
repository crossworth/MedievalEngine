#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <string>

namespace ME {

class Clipboard {
public:
	static std::string getData();
	static void setData(const std::string& data);
};

}


#endif // CLIPBOARD_H