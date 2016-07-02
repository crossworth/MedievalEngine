#include "Clipboard.h"
#include "Helper/OS.h"

#ifdef _OS_MAC
	#include "Helper/Clipboard_imp_macos.h"
#endif


#ifdef _OS_WIN
	#include "Helper/Clipboard_imp_windows.h"
#endif

using namespace ME;

String Clipboard::getData() {
#ifdef _OS_MAC
	return MacOSXGetClipboardData();
#elif defined(_OS_WIN)
	return WindowsGetClipboardData();
#else
	// TODO(Pedro): Implement the Unix version
	return "";
#endif
}


void Clipboard::setData(const String& data) {
#ifdef _OS_MAC
	MacOSXSetClipboardData(data);
#elif defined(_OS_WIN)
	return WindowsSetClipboardData(data);
#else

#endif
}
