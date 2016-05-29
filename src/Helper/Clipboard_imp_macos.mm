#import <Cocoa/Cocoa.h>
#include "Clipboard_imp_macos.h"


std::string MacOSXGetClipboardData() {
	NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];

    if (![[pasteboard types] containsObject:NSStringPboardType]) {
        std::cout << "Cocoa Failed to retrieve string from pasteboard" << std::endl;
    }

    NSString* object = [pasteboard stringForType:NSStringPboardType];
    if (!object) {
        std::cout << "Cocoa Failed to retrieve object from pasteboard" << std::endl;
    }

    return std::string([object UTF8String]);
}


void MacOSXSetClipboardData(const std::string& data) {
	NSArray* types = [NSArray arrayWithObjects:NSStringPboardType, nil];

    NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard declareTypes:types owner:nil];
    [pasteboard setString:[NSString stringWithUTF8String:data.c_str()]
                  forType:NSStringPboardType];
}
