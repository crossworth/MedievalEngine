#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include "Helper/String.h"

namespace ME {

class Clipboard {
public:
	static String getData();
	static void setData(const String& data);
};

}


#endif // CLIPBOARD_H