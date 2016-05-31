#import <Cocoa/Cocoa.h>
#include "Clipboard_imp_macos.h"


ME::String MacOSXGetClipboardData() {
	NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];

    if (![[pasteboard types] containsObject:NSStringPboardType]) {
        std::cout << "Cocoa Failed to retrieve string from pasteboard" << std::endl;
    }

    NSString* object = [pasteboard stringForType:NSStringPboardType];
    if (!object) {
        std::cout << "Cocoa Failed to retrieve object from pasteboard" << std::endl;
    }

    return ME::String(ME::String::UTF8_to_wstring([object UTF8String]));
}


void MacOSXSetClipboardData(const ME::String& data) {
    std::string tmp = ME::String::wstring_to_UTF8(data.getWideString());

	NSArray* types = [NSArray arrayWithObjects:NSStringPboardType, nil];

    NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard declareTypes:types owner:nil];
    [pasteboard setString:[NSString stringWithUTF8String:tmp.c_str()]
                  forType:NSStringPboardType];
}
