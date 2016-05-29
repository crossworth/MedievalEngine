#include "Clipboard.h"
#include "Helper/OS.h"

#ifdef _OS_MAC
	#include "Helper/Clipboard_imp_macos.h"
#endif

using namespace ME;


std::string Clipboard::getData() {
#ifdef _OS_MAC
	return MacOSXGetClipboardData();
#else
	// TODO(Pedro): Implement Windows and Unix version
	return "";
#endif
}


void Clipboard::setData(const std::string& data) {
#ifdef _OS_MAC
	MacOSXSetClipboardData(data);
#else

#endif
}
