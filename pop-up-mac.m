#import <Cocoa/Cocoa.h>
#include "snake.cpp" // Include your C++ file

// Interface for the AppDelegate
@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (strong) NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    // Start the Snake game (call the startSnakeGame function from snake.cpp)
    startSnakeGame();
}

@end

// Replacement for MessageBox in C++ using NSAlert
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

// Main function to set up the macOS application
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        app.delegate = delegate;
        return NSApplicationMain(argc, argv);
    }
}
