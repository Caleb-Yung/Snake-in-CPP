#import <Cocoa/Cocoa.h>

// Expose the function to C++ with "extern C"
extern "C" void showGameOverMessage() {
    @autoreleasepool {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Game Over"];
        [alert setInformativeText:@"You hit the wall or your tail"];
        [alert addButtonWithTitle:@"OK"];
        [alert setAlertStyle:NSAlertStyleWarning];
        [alert runModal]; // Display the alert
    }
}
